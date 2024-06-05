#pragma once

#include "generic/model/type.hpp"

using stx::gen::Type;

namespace stx {

    namespace cpp {

        namespace t {
            Type make_double() { return {"double"}; }

            Type make_bool() { return {"bool"}; }

            Type make_empty() { return {""}; }
            
            Type make_enum() { return {"enum"}; }
            
            Type make_struct() { return {"struct"}; }

            Type make_cint() { return {"int"}; }

            Type make_cstdint(const std::string &name) { return Type{name, "cstdint"}; }
            Type make_int8() { return make_cstdint("int8_t"); }
            Type make_int16() { return make_cstdint("int16_t"); }
            Type make_int32() { return make_cstdint("int32_t"); }
            Type make_int64() { return make_cstdint("int64_t"); }

            Type make_uint8() { return make_cstdint("uint8_t"); }
            Type make_uint16() { return make_cstdint("uint16_t"); }
            Type make_uint32() { return make_cstdint("uint32_t"); }
            Type make_uint64() { return make_cstdint("uint64_t"); }

            Type make_void() { return {"void"};}

            Type make_ptr(const Type& type) { return {type.name + '*'}; }

        }; /* Types */

    }; /* Cpp */

}; /* Syntax */