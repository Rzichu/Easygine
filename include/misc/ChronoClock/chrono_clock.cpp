#include "chrono_clock.h"

#include <sstream>

namespace aether::chrono_clock {
    void Calendar::loadLocal() {
        std::time_t loadTimeT = std::time(NULL);
        m_Calendar = std::localtime(&loadTimeT);

        this->m_Calendar->tm_mon += 1;
        this->m_Calendar->tm_year += 1'900;
    }

    void Calendar::loadUTC() {
        std::time_t loadTimeT = std::time(NULL);
        m_Calendar = std::gmtime(&loadTimeT);

        this->m_Calendar->tm_mon += 1;
        this->m_Calendar->tm_year += 1'900;
    }
    
    std::string Calendar::toString() {
        std::stringstream date;
        
        date << this->m_Calendar->tm_mday << "/" << this->m_Calendar->tm_mon << "/" << this->m_Calendar->tm_year
            << "_" << this->m_Calendar->tm_hour << "-" << this->m_Calendar->tm_min << "-" << this->m_Calendar->tm_sec;

        return date.str();
    }
}