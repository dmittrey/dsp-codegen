#pragma once

#include "generic/model/rval.hpp"

using stx::gen::Type;

namespace stx {

    namespace c {

        struct RVal final : gen::RVal {
        public:
            const uint64_t size;

        public:
            RVal(const Type& type, const std::string& name, uint64_t size) : gen::RVal(type, name), size(size) {}
            RVal(const Type& type, const std::string& name) : RVal(type, name, 0) {}

        public:
            RVal ptr() {
                return {{type.name + '*'}, name + "_p"};
            };

        public:
            std::string code() const override {
                return type.name + ' ' + name + (size != 0 ? ':' + std::to_string(size) : "");
            }
        };

    }; /* c */

}; /* syntax */