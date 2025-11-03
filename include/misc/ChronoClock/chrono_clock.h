#pragma once

#include <ctime>
#include <string>

namespace aether {
    namespace chrono_clock {
        class Calendar;

        class Calendar {
        public:
            void loadLocal();
            
            void loadUTC();

            std::string toString();

            inline const std::tm * getTm() const {
                return this->m_Calendar;
            }
            
            inline int seconds() const {
                return this->m_Calendar->tm_sec;
            }
            
            inline int minutes() const {
                return this->m_Calendar->tm_min;
            }
            
            inline int hours() const {
                return this->m_Calendar->tm_hour;
            }
            
            inline int weekDay() const {
                return this->m_Calendar->tm_wday;
            }
            
            inline int monthDay() const {
                return this->m_Calendar->tm_mday;
            }
            
            inline int month() const {
                return this->m_Calendar->tm_mon;
            }
            
            inline int yearDay() const {
                return this->m_Calendar->tm_yday;
            }
            
            inline int year() const {
                return this->m_Calendar->tm_year;
            }

        public:
            Calendar()           = default;
            virtual ~Calendar()  = default;

            Calendar(const Calendar &copy)                = default;
            Calendar & operator=(const Calendar &copy)    = default;

        private:
            std::tm *m_Calendar;
        };
    }
}