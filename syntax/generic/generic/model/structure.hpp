#pragma once

#include "model.hpp"
#include "type.hpp"

namespace stx {

    namespace gen {

        template<typename T>
        struct Structure : Model {
            public:
                Type type;
                const std::optional<std::string> name; /* Anon structures */
            protected:
                std::vector<std::unique_ptr<T>> fields_ = {}; /* Nested structures, Comments */

            public:
                Structure(const Type &type, const std::optional<std::string> &name) : type(type), name(name) {}

            public:
                template<typename U>
                Structure& field_add(const IModel& field) & {
                    headers_.insert(headers_.end(), field.headers().begin(), field.headers().end());
                    fields_.push_back(std::make_unique<U>(field)); 
                    return *this;
                }

                template<typename U>
                Structure& field_add(const U& field) & {
                    static_assert(!std::is_abstract<U>::value, "T must be non abstract");
                    static_assert(std::is_base_of<T, U>::value, "Field must inherit from T");
                    static_assert(std::is_convertible_v<U, std::string>, "T must be implicitly convertible to std::string");

                    fields_.push_back(std::make_unique<U>(field)); 
                    return *this;
                }
        };

    }; /* generic */

}; /* syntax */