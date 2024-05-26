#pragma once

#include <memory>
#include <iostream>
#include <fstream>

#include "syntax/interface/iserializer.hpp"

namespace Generate {

    struct Serializer : ISerializer {
    protected:
        const std::unique_ptr<std::ostream> out_;

    public:
        void serialize(ILayout& layout) const override {
            *out_ << layout.render() << std::endl;
        }

    protected:
        Serializer(std::unique_ptr<std::ostream> out) : out_(std::move(out)) {}
    };

}; /* Generate */