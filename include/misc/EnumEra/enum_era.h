#pragma once

#include <string>

namespace aether {
    namespace enumera {
        template<typename ENUMERATED_TYPE>
        constexpr auto enumToNum(const ENUMERATED_TYPE value)
            -> typename std::underlying_type<ENUMERATED_TYPE>::type
            {
            return static_cast<typename std::underlying_type<ENUMERATED_TYPE>::type>(value);
        }

        std::string stringFromEnum(const std::string &enum_value);
    }

#define enumera_TO_STRING(enum_val) aether::enumera::stringFromEnum(#enum_val)
}