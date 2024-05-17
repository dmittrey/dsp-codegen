#pragma once

#include "model.hpp"

namespace Generate {

    struct Structure : Model {
        public:
            const Type type;
            const std::optional<std::string> name; /* Anon structures */
        protected:
            std::vector<std::unique_ptr<IModel>> fields_ = {}; /* Nested strutures, Comments */

        protected:
            Structure(const Type &type, const std::optional<std::string> &name) : type(type), name(name) {}

        protected:
            Structure& field_add(std::unique_ptr<IModel> field) & { 
                headers_.insert(headers_.end(), field->headers().begin(), field->headers().end());
                fields_.emplace_back(std::move(field)); 
                return *this;
            }
    };

}; /* Generate */