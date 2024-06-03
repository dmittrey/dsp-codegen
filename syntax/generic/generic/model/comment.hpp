#pragma once

#include "model.hpp"

namespace stx {

    namespace gen {

        struct Comment : Model {
        public:
            const std::string text;
    
        public:
            Comment(const std::string& text) : text(text) {}
        };

    }; /* generic */

}; /* syntax */