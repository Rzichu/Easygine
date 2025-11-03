#include "log_sys.h"

#include <fstream>

namespace aether::lgs {
    LOGSYS_MSGLVL LOGSYS_BROADCAST::m_LogLvl = LOG_LVL;

    LOGSYS_LOGGER::LOGSYS_LOGGER(const std::string &name
                , const std::string &dest_file)
        : m_Name(std::forward<const std::string &>(name))
        , m_DestFile(std::forward<const std::string &>(dest_file))
        {}

    void LOGSYS_LOGGER::wipeData() {
        this->m_DestFile = "cmd";
        this->m_Message.str(std::string());
    }

    void LOGSYS_BROADCAST::write(LOGSYS_LOGGER &logger, double time, LOGSYS_MSGLVL lvl, bool clear, bool format, const char *func, const char *src, unsigned long long line) {
        static std::mutex MTX;
        std::lock_guard<std::mutex> guard(MTX);
        static LOGSYS_BROADCAST broadcast;

        if (lvl >= LOGSYS_BROADCAST::m_LogLvl) {
            if (format) {
                broadcast.m_Sec = time / 1000;
                if (broadcast.m_Sec > 59) {
                    broadcast.m_Min = broadcast.m_Sec / 60;
                    broadcast.m_Sec = broadcast.m_Sec - (broadcast.m_Min * 60);
                    if (broadcast.m_Min > 59) {
                        broadcast.m_Hr = broadcast.m_Min / 60;
                        broadcast.m_Min = broadcast.m_Min - (broadcast.m_Hr * 60);
                    }
                }

                if (logger.getDestFile() == "cmd") {
                    std::cout << "[_Log_#" << broadcast.m_LogNumber[0]++ << "_]"
                        << "\n|-{ Logger name }:    " << logger.getName()
                        << "\n|-{ In file }:        " << src
                        << "\n|-{ At line }:        " << line
                        << "\n|-{ On thread (ID) }: " << logger.loadThreadId()
                        << "\n|-{ In process }:     " << func
                        << "\n|-{ At time }:        " << time
                            << " ms (" << broadcast.m_Hr << " hours : " << broadcast.m_Min
                            << " minutes : " << broadcast.m_Sec << " seconds)"
                        << "\n|-{ Of level }:       "
                            << broadcast.m_MsgLvl[static_cast<std::underlying_type<LOGSYS_MSGLVL>::type>(lvl)]
                        << "\n|-{ Message }:        " << logger.getMsg().str()
                        << "\n\n--------------------\n\n";
                }
                else {
                    std::ofstream outLog(logger.getDestFile(), std::ios::app);
                    if (outLog.is_open()) {
                        outLog << "[_Log_#" << broadcast.m_LogNumber[1]++ << "_]"
                            << "\n|-{ Logger name }:    " << logger.getName()
                            << "\n|-{ In file }:        " << src
                            << "\n|-{ At line }:        " << line
                            << "\n|-{ On thread (ID) }: " << logger.loadThreadId()
                            << "\n|-{ In process }:     " << func
                            << "\n|-{ At time }:        " << time
                                << " ms (" << broadcast.m_Hr << " hours : " << broadcast.m_Min
                                << " minutes : " << broadcast.m_Sec << " seconds)"
                            << "\n|-{ Of level }:       "
                                << broadcast.m_MsgLvl[static_cast<std::underlying_type<LOGSYS_MSGLVL>::type>(lvl)]
                            << "\n|-{ Message }:        " << logger.getMsg().str()
                            << "\n\n--------------------\n\n";
                        outLog.close();
                    }
                    else {
                        std::cout << "Could not open \"" << logger.getDestFile()
                            << "\" destination file.\n";
                    }
                }
            } else {
                if (logger.getDestFile() == "cmd") {
                    std::cout << logger.getMsg().str() << "\n\n";
                }
                else {
                    std::ofstream outLog(logger.getDestFile(), std::ios::app);
                    if (outLog.is_open()) {
                        outLog << logger.getMsg().str() << "\n";
                        outLog.close();
                    }
                    else {
                        std::cout << "Could not open \"" << logger.getDestFile()
                            << "\" destination file.\n";
                    }
                }
            }
        }
        if (clear) {
            logger.setMsg().str(std::string());
        }
    }

    std::string LOGSYS_BROADCAST::out(LOGSYS_LOGGER &logger, double time, LOGSYS_MSGLVL lvl, bool clear, bool format, const char *func, const char *src, unsigned long long line) {
        static std::mutex MTX;
        std::lock_guard<std::mutex> guard(MTX);
        static LOGSYS_BROADCAST broadcast;

        std::stringstream sstream;

        if (lvl >= LOGSYS_BROADCAST::m_LogLvl) {
            if (format) {
                broadcast.m_Sec = time / 1000;
                if (broadcast.m_Sec > 59) {
                    broadcast.m_Min = broadcast.m_Sec / 60;
                    broadcast.m_Sec = broadcast.m_Sec - (broadcast.m_Min * 60);
                    if (broadcast.m_Min > 59) {
                        broadcast.m_Hr = broadcast.m_Min / 60;
                        broadcast.m_Min = broadcast.m_Min - (broadcast.m_Hr * 60);
                    }
                }
                
                sstream << "[_Log_#" << broadcast.m_LogNumber[0]++ << "_]"
                    << "\n|-{ Logger name }:    " << logger.getName()
                    << "\n|-{ In file }:        " << src
                    << "\n|-{ At line }:        " << line
                    << "\n|-{ On thread (ID) }: " << logger.loadThreadId()
                    << "\n|-{ In process }:     " << func
                    << "\n|-{ At time }:        " << time
                        << " ms (" << broadcast.m_Hr << " hours : " << broadcast.m_Min
                        << " minutes : " << broadcast.m_Sec << " seconds)"
                    << "\n|-{ Of level }:       "
                        << broadcast.m_MsgLvl[static_cast<std::underlying_type<LOGSYS_MSGLVL>::type>(lvl)]
                    << "\n|-{ Message }:        " << logger.getMsg().str()
                    << "\n\n--------------------\n\n";
            }
            else {
                sstream << logger.getMsg().str() << "\n";
            }
        }
        if (clear) {
            logger.setMsg().str(std::string());
        }

        return sstream.str();
    }

    void LOGSYS_TIMER::stop() {
        if (!this->m_Stopped) {
            this->calculateTime();
            this->m_Stopped = true;
        }
    }

    double LOGSYS_TIMER::restart() {
        double curr_time = getTime();
        if (this->m_Stopped) {
            this->m_Stopped = false;
        }
        this->m_startTimePoint = std::chrono::steady_clock::now();
        return curr_time;
    }

    double LOGSYS_TIMER::getTime() {
        if (!this->m_Stopped) {
            this->calculateTime();
        }
        return this->m_Duration;
    }

    void LOGSYS_TIMER::calculateTime() {
        auto endTimePoint = std::chrono::steady_clock::now();

        auto start = std::chrono::time_point_cast<std::chrono::microseconds>(this->m_startTimePoint).time_since_epoch().count();
        auto end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimePoint).time_since_epoch().count();
    
        auto duration = end - start;
        this->m_Duration = duration * 0.001;
    }
}