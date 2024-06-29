#pragma once

#include "generic/model.hpp"
#include "type.hpp"

namespace stx {

    namespace gen {

        template <typename T>
        struct Structure : Model {
        public:
            const Type type;
            const std::optional<std::string> name; /* Anon structures */
        protected:
            std::vector<std::unique_ptr<T>> fields_ = {}; /* Nested structures, Comments */

        public:
            Structure(const Type &type, const std::optional<std::string> &name) : type(type), name(name) {}

        public:
            template<typename U>
            Structure& field_add(const U& field) & {
                fields_.push_back(std::make_unique<U>(field)); 
                return *this;
            }
        };

    }; /* generic */

}; /* syntax */