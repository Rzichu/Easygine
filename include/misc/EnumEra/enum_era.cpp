#include "enum_era.h"

namespace aether::enumera {
    std::string stringFromEnum(const std::string &enum_value) {
        unsigned long long char_pos = enum_value.rfind(':');
        if (char_pos != std::string::npos) {
            return enum_value.substr(char_pos + 1ull);
        }
        else {
            return enum_value;
        }
    }
}