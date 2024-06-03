#pragma once

#include "generic/model/comment.hpp"

namespace stx {

    namespace cpp {

    struct Comment final : gen::Comment {
    public:
        Comment(const std::string& text) : gen::Comment(text) {}

    public:
        std::string code() override {
            return "/* " + text + " */";
        }
    };

    }; /* cpp */

}; /* syntax */