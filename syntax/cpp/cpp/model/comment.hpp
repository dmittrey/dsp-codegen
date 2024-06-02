#pragma once

#include "generic/model/comment.hpp"

namespace Syntax {

    struct CppComment final : Comment {
    public:
        CppComment(const std::string& text) : Comment(text) {}

    public:
        std::string code() const override {
            return "/* " + text + " */";
        }
    };

}; /* Syntax */