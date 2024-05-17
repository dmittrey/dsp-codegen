#pragma once

#include "generic/rval.hpp"

namespace Generate {

    struct CppRVal final : RVal {
    private:
        uint64_t size_;

    public:
        CppRVal(const Type& type, const std::string& name, uint64_t size) : RVal(type, name), size_(size) {}
        CppRVal(const Type& type, const std::string& name) : CppRVal(type, name, 0) {}

        uint64_t size() const { return size_; }

    public:
        std::string code() const override {
            return type.name + ' ' + name + (size_ != 0 ? ':' + std::to_string(size_) : "");
        }
    };

}; /* Generate */