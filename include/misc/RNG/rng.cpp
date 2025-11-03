#include "rng.h"

namespace aether::rng {
    bool SimpleRandom::getBool(double probability) {
        m_Gen.seed(this->m_RD());
        std::bernoulli_distribution dist_bool(probability);
        return dist_bool(m_Gen);
    }

    int SimpleRandom::getInt(int min, int max) {
        m_Gen.seed(this->m_RD());
        std::uniform_int_distribution<int> dist_int(min, max);
        return dist_int(m_Gen);
    }

    unsigned int SimpleRandom::getUint(unsigned int min, unsigned int max) {
        m_Gen.seed(this->m_RD());
        std::uniform_int_distribution<unsigned int> dist_uint(min, max);
        return dist_uint(m_Gen);
    }

    long long SimpleRandom::getLong(long long min, long long max) {
        m_Gen.seed(this->m_RD());
        std::uniform_int_distribution<long long> dist_llong(min, max);
        return dist_llong(m_Gen);
    }

    unsigned long long SimpleRandom::getUlong(unsigned long long min, unsigned long long max) {
        m_Gen.seed(this->m_RD());
        std::uniform_int_distribution<unsigned long long> dist_ullong(min, max);
        return dist_ullong(m_Gen);
    }

    float SimpleRandom::getFloat(float min, float max) {
        m_Gen.seed(this->m_RD());
        std::uniform_real_distribution<float> dist_float(min, max);
        return dist_float(m_Gen);
    }

    double SimpleRandom::getDouble(double min, double max) {
        m_Gen.seed(this->m_RD());
        std::uniform_real_distribution<double> dist_double(min, max);
        return dist_double(m_Gen);
    }

    long double SimpleRandom::getLongDouble(long double min, long double max) {
        m_Gen.seed(this->m_RD());
        std::uniform_real_distribution<long double> dist_ldouble(min, max);
        return dist_ldouble(m_Gen);
    }
}