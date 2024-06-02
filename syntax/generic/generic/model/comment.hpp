#pragma once

#include "model.hpp"

namespace Syntax {

    struct Comment : Model {
    public:
        const std::string text;

    public:
        Comment(const std::string& text) : text(text) {}
    };

}; /* Syntax */