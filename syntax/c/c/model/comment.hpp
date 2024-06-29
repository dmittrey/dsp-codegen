#pragma once

#include "generic/model.hpp"

namespace stx {

    namespace c {

    struct Comment final : gen::Model {
    public:
        const std::string text;
    
    public:
        Comment(const std::string& text) : text(text) {}

    public:
        std::string code() const override {
            return "/* " + text + " */";
        }
    };

    }; /* c */

}; /* syntax */