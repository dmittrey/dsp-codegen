#pragma once

#include "model.hpp"

namespace Generate {

    struct Comment : Model {
    public:
        const std::string text;

    public:
        Comment(const std::string& text) : text(text) {}
    };

}; /* Generate */