#pragma once

#include "generic/model/rval.hpp"

using stx::gen::Type;

namespace stx {

    namespace c {

        struct RVal : gen::RVal {
        public:
            const uint64_t size;

        public:
            RVal(const Type& type, const std::string& name, uint64_t size) : gen::RVal(type, name), size(size) {}
            RVal(const Type& type, const std::string& name) : RVal(type, name, 0) {}

        public:
            std::string code() const override {
                return type.name + ' ' + name + (size != 0 ? ':' + std::to_string(size) : "");
            }
        };

    }; /* c */

}; /* syntax */