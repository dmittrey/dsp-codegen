#pragma once

#include "interface/type.hpp"

using Utility::Type;

namespace Generate {

    namespace Types {

        Type make_uint(const std::string &name) {
            return Type{name, "cstdint"};
        }

        Type make_uint8() {
            return make_uint("uint8_t");
        }

        Type make_uint16() {
            return make_uint("uint16_t");
        }

        Type make_uint32() {
            return make_uint("uint32_t");
        }

        Type make_uint64() {
            return make_uint("uint64_t");
        }

    }; /* Types */

}; /* Generate */