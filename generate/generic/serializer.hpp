#pragma once

#include <memory>
#include <iostream>
#include <fstream>

#include "interface/iserializer.hpp"

namespace Generate {

    struct Serializer : ISerializer {
    protected:
        std::unique_ptr<std::ostream> out_;

    public:
        Serializer() = delete;
        Serializer(Serializer&& obj) = delete;
        Serializer(std::unique_ptr<std::ostream> out) : out_(std::move(out)) {}

        void serialize(const ILayout& layout) override {
            *out_ << layout.render() << std::endl;
        };
    };

}; /* Generate */