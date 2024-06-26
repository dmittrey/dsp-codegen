#pragma once

#include "model.hpp"
#include "type.hpp"

namespace stx {

    namespace gen {

        struct Structure : Model {
            public:
                Type type;
                const std::optional<std::string> name; /* Anon structures */
            protected:
                std::vector<std::unique_ptr<IModel>> fields_ = {}; /* Nested structures, Comments */

            public:
                Structure(const Type &type, const std::optional<std::string> &name) : type(type), name(name) {}

            protected:
            // Можно проверить на возможность вызвать оператор >> или имплисит к строке
                template<typename T>
                Structure& field_add(const T& field) & { 
                    static_assert(std::is_base_of<IModel, T>::value, "Field must inherit from IModel");
                    static_assert(!std::is_abstract<T>::value, "T must be non abstract");

                    headers_.insert(headers_.end(), field.headers().begin(), field.headers().end());
                    fields_.push_back(std::make_unique<T>(field)); 
                    return *this;
                }
        };

    }; /* generic */

}; /* syntax */