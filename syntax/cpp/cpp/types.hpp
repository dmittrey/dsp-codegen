#pragma once

#include "generic/model/type.hpp"

using stx::gen::Type;

namespace stx {

    namespace cpp {

        namespace t {
            Type Double() { return {"double"}; }

            Type Bool() { return {"bool", "stdbool.h"}; }

            Type Empty() { return {""}; }
            
            Type Enum() { return {"enum"}; }
            
            Type Struct() { return {"struct"}; }

            Type Cint() { return {"int"}; }

            Type Cstdint(const std::string &name) { return Type{name, "stdint.h"}; }
            Type Int8() { return Cstdint("int8_t"); }
            Type Int16() { return Cstdint("int16_t"); }
            Type Int32() { return Cstdint("int32_t"); }
            Type Int64() { return Cstdint("int64_t"); }

            Type Uint8() { return Cstdint("uint8_t"); }
            Type Uint16() { return Cstdint("uint16_t"); }
            Type Uint32() { return Cstdint("uint32_t"); }
            Type Uint64() { return Cstdint("uint64_t"); }

            Type Void() { return {"void"};}

        }; /* Types */

    }; /* Cpp */

}; /* Syntax */