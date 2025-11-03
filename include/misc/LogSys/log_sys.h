#pragma once

#include <future>
#include <iostream>
#include <sstream>
#include <chrono>
#include <utility>

#define LOG_LVL         aether::lgs::LOGSYS_MSGLVL::Debug
#ifdef LOG_LVL_INFO
#undef LOG_LVL
#define LOG_LVL         aether::lgs::LOGSYS_MSGLVL::Info;
#endif
#ifdef LOG_LVL_WARN
#undef LOG_LVL
#define LOG_LVL         aether::lgs::LOGSYS_MSGLVL::Warning;
#endif
#ifdef LOG_LVL_ERROR
#undef LOG_LVL
#define LOG_LVL         aether::lgs::LOGSYS_MSGLVL::Error;
#endif
#ifdef LOG_LVL_FATAL
#undef LOG_LVL
#define LOG_LVL         aether::lgs::LOGSYS_MSGLVL::FatalError;
#endif

namespace aether {
    namespace lgs {
        class LOGSYS_TIMER;
        class LOGSYS_BROADCAST;
        class LOGSYS_LOGGER;
        enum class LOGSYS_MSGLVL;

        typedef LOGSYS_TIMER    Timer;
        typedef LOGSYS_LOGGER   Logger;
        typedef LOGSYS_MSGLVL   MsgLvl;

        enum class LOGSYS_MSGLVL {
              Debug
            , Info
            , Warning
            , Error
            , FatalError
        };

        class LOGSYS_LOGGER {
            friend class LOGSYS_BROADCAST;
        public:
            inline const std::string & getName() const {
                return this->m_Name;
            }

            inline const std::string & getDestFile() const {
                return this->m_DestFile;
            }

            inline const std::stringstream & getMsg() const {
                return this->m_Message;
            }

            inline std::stringstream & setMsg() {
                return this->m_Message;
            }

            inline void setName(const std::string &name = "Unnamed") {
                this->m_Name = std::forward<const std::string &>(name);
            }
            
            inline void setDestFile(const std::string &dest_file = "cmd") {
                this->m_DestFile = std::forward<const std::string &>(dest_file);
            }

            void wipeData();

        public:
            LOGSYS_LOGGER(const std::string &name = "Unnamed"
                    , const std::string &dest_file = "cmd");

            virtual ~LOGSYS_LOGGER()    = default;

            LOGSYS_LOGGER(const LOGSYS_LOGGER &copy)                = delete;
            LOGSYS_LOGGER & operator=(const LOGSYS_LOGGER &copy)    = delete;

        private:
            inline const uint32_t loadThreadId() const {
                return uint32_t(std::hash<std::thread::id>{}(std::this_thread::get_id()));
            }

        private:
            std::string m_Name {"Unnamed"};
            std::string m_DestFile {"cmd"};
            std::stringstream m_Message;
        };


        class LOGSYS_BROADCAST {
        public:
            static void write(LOGSYS_LOGGER &logger, double time, LOGSYS_MSGLVL lvl, bool clear, bool format, const char *func, const char *src, unsigned long long line);

            static std::string out(LOGSYS_LOGGER &logger, double time, LOGSYS_MSGLVL lvl, bool clear, bool format, const char *func, const char *src, unsigned long long line);
        
        public:
            virtual ~LOGSYS_BROADCAST() = default;

            LOGSYS_BROADCAST(const LOGSYS_BROADCAST &copy)              = delete;
            LOGSYS_BROADCAST & operator=(const LOGSYS_BROADCAST &copy)  = delete;
        
        private:
            LOGSYS_BROADCAST() = default;

        private:
            static LOGSYS_MSGLVL m_LogLvl;
            std::string m_MsgLvl[5] {"Debug", "Info", "Warning", "Error", "Critical Error"};
            unsigned long long m_LogNumber[2] {0ull, 0ull};
            unsigned long long m_Sec {0ull}, m_Min {0ull}, m_Hr {0ull};
        };


        class LOGSYS_TIMER {
        public:
            void stop();

            double restart();

            double getTime();
        
        public:
            LOGSYS_TIMER()          = default;
            virtual ~LOGSYS_TIMER() = default;

            LOGSYS_TIMER(const LOGSYS_TIMER &copy)              = delete;
            LOGSYS_TIMER & operator=(const LOGSYS_TIMER &copy)  = delete;

        private:
            void calculateTime();

        private:
            std::chrono::time_point<std::chrono::steady_clock> m_startTimePoint {std::chrono::steady_clock::now()};
            double m_Duration {0.0};
            bool m_Stopped {false};
        };
    }
}

#ifdef LOGSYS
#define lgs_LOG(logger, time, lvl, clear, format)   aether::lgs::LOGSYS_BROADCAST::write(logger, time, lvl, clear, format, __PRETTY_FUNCTION__, __FILE__, __LINE__)
#define lgs_OUT(logger, time, lvl, clear, format)   aether::lgs::LOGSYS_BROADCAST::out(logger, time, lvl, clear, format, __PRETTY_FUNCTION__, __FILE__, __LINE__)

#define lgs_LOGGER_SET_NAME(logger, name)   logger.setName(name)
#define lgs_LOGGER_SET_FILE(logger, file)   logger.setDestFile(file)

#define lgs_LOGGER_GET_NAME(logger)         logger.getName()
#define lgs_LOGGER_GET_FILE(logger)         logger.getDestFile()
#define lgs_LOGGER_GET_MSG(logger)          logger.getMsg()

#define lgs_LOGGER_WIPE(logger)             logger.wipeData()

#define lgs_LOGGER_MSG(logger)              logger.setMsg()
#define lgs_MSG(message)                    << message

#define lgs_TIMER_STOP(timer)               timer.stop()
#define lgs_TIMER_RESTART(timer)            timer.restart()
#define lgs_TIMER_TIME(timer)               timer.getTime()
#else
#define lgs_LOG(logger, time, lvl, clear, format)
#define lgs_OUT(logger, time, lvl, clear, format)

#define lgs_LOGGER_SET_NAME(logger, name)
#define lgs_LOGGER_SET_FILE(logger, file)

#define lgs_LOGGER_GET_NAME(logger)
#define lgs_LOGGER_GET_FILE(logger)
#define lgs_LOGGER_GET_MSG(logger)

#define lgs_LOGGER_WIPE(logger)

#define lgs_LOGGER_MSG(logger)
#define lgs_MSG(message)

#define lgs_TIMER_STOP(timer)
#define lgs_TIMER_RESTART(timer)
#define lgs_TIMER_TIME(timer)
#endif