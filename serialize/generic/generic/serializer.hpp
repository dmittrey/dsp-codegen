#pragma once

#include <memory>
#include <iostream>
#include <fstream>

#include "iserializer.hpp"

namespace Serialize {

    struct Serializer final : ISerializer {
    protected:
        const std::unique_ptr<std::ostream> out_;

    public:
        Serializer(std::unique_ptr<std::ostream> out) : out_(std::move(out)) {}
        
        void serialize(stx::ILayout& layout) const override {
            *out_ << layout.code() << std::endl;
        }
    };

}; /* Serialize */