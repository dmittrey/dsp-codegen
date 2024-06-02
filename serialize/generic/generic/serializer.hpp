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
        
        void serialize(Syntax::ILayout& layout) const override {
            *out_ << layout.render() << std::endl;
        }
    };

}; /* Serialize */