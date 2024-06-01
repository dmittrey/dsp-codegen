#pragma once

#include "model.hpp"

namespace Generate {

    struct Type final : Model {
    public:
        const std::string name;

    public:
        Type(const std::string& name) : name(name) {}
        Type(const std::string& name, const std::string& header) : name(name) { headers_.push_back(header); }

    public:
        std::string code() const override { return name; }
    };

}; /* Generate */