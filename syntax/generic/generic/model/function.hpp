#pragma once

#include "model.hpp"

namespace stx {

    namespace gen {

        struct Function : Model {
            public:
                Type type;
                const std::string name;
            protected:
                std::vector<std::unique_ptr<IModel>> params_ = {}; /* Nested strutures, Comments */

            public:
                Function(const Type &type, const std::string &name) : type(type), name(name) {}

            protected:
                virtual const std::string payload() const = 0;

                template<typename T>
                Function& param_add(const T& field) & { 
                    static_assert(std::is_base_of<IModel, T>::value, "Field must inherit from IModel");
                    static_assert(!std::is_abstract<T>::value, "T must be non abstract");

                    headers_.insert(headers_.end(), field.headers().begin(), field.headers().end());
                    params_.push_back(std::make_unique<T>(field)); 
                    return *this;
                }
        };

    }; /* generic */

}; /* syntax */