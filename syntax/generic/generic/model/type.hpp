#pragma once

#include "generic/model.hpp"

namespace stx {

    namespace gen {

        struct Type final : Model {
        public:
            const std::string name;

        public:
            Type(const std::string& name) : name(name) {}
            Type(const std::string& name, const std::string& header) : name(name) { push_header(header); }

        public:
            std::string code() const override { return name; }
        };

    }; /* generic */

}; /* syntax */