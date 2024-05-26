#pragma once

#include "syntax/generic/model/rval.hpp"

namespace Generate {

    struct CppRVal final : RVal {
    public:
        const uint64_t size;

    public:
        CppRVal(const Type& type, const std::string& name, uint64_t size) : RVal(type, name), size(size) {}
        CppRVal(const Type& type, const std::string& name) : CppRVal(type, name, 0) {}

    public:
        std::string code() const override {
            return type.name + ' ' + name + (size != 0 ? ':' + std::to_string(size) : "");
        }
    };

}; /* Generate */