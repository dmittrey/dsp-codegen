#pragma once

#include "generic/model/comment.hpp"

namespace Generate {

    struct CppComment final : Comment {
    public:
        CppComment(const std::string& text) : Comment(text) {}

    public:
        std::string code() const override {
            return "/* " + text + " */";
        }
    };

}; /* Generate */