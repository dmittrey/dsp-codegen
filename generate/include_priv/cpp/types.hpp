#pragma once

#include "generic/model/type.hpp"

namespace Generate {

    namespace Cpp {

        namespace Types {

            Type make_bool() { return "bool"; }

            Type make_empty() { return ""; }
            
            Type make_enum() { return "enum"; }
            
            Type make_int() { return "int"; }
            
            Type make_struct() { return "struct"; }
            
            Type make_uint(const std::string &name) { return Type{name, "cstdint"}; }
            Type make_uint8() { return make_uint("uint8_t"); }
            Type make_uint16() { return make_uint("uint16_t"); }
            Type make_uint32() { return make_uint("uint32_t"); }
            Type make_uint64() { return make_uint("uint64_t"); }

            Type make_void() { return "void";}

        }; /* Types */

    }; /* Cpp */

}; /* Generate */