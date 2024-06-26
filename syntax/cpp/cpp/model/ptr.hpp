#pragma once

#include "generic/model/rval.hpp"

using stx::gen::Type;

namespace stx {

    namespace cpp {

        struct Ptr final : RVal {
        public:
            Ptr(const Type& type, const std::string& name) : RVal(Type(type.name + '*'), name + "_p") { }

        public:
            std::string code() override {
                return type.name + ' ' + name + (size != 0 ? ':' + std::to_string(size) : "");
            }
        };

    }; /* cpp*/

}; /* syntax */