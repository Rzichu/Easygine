#pragma once

#include <random>

namespace aether {
    namespace rng {
        class SimpleRandom;

        class SimpleRandom {
        public:
            bool getBool(double probability = 0.5);
            
            int getInt(int min = 0, int max = 100);
            
            unsigned int getUint(unsigned int min = 0u, unsigned int max = 100u);
            
            long long getLong(long long min = 0ll, long long max = 100ll);
            
            unsigned long long getUlong(unsigned long long min = 0ull, unsigned long long max = 100ull);
            
            float getFloat(float min = 0.0f, float max = 1.0f);
            
            double getDouble(double min = 0.0, double max = 1.0);
            
            long double getLongDouble(long double min = 0.0l, long double max = 1.0l);

        public:
            SimpleRandom()          = default;
            virtual ~SimpleRandom() = default;

            SimpleRandom(const SimpleRandom &copy)              = default;
            SimpleRandom & operator=(const SimpleRandom &copy)  = default;
        
        private:
            std::random_device m_RD;
            std::mt19937 m_Gen;
        };
    }
}