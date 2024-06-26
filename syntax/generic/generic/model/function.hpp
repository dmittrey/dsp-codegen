#pragma once

#include "type.hpp"

#include "generic/clojure.hpp"
#include "generic/model/model.hpp"

namespace stx {

    namespace gen {

        struct Function : Model {
            public:
                Type type;
                const std::string name;
            protected:
                std::vector<std::unique_ptr<IModel>> params_ = {}; /* Nested strutures, Comments */
                std::vector<std::string> body_lines_ = {};

            public:
                Function(const Type &type, const std::string &name) : type(type), name(name) {}

            protected:
                virtual const std::string payload() const = 0;

            public:
                template<typename T>
                Function& params_set(std::initializer_list<T> params) & { 
                    static_assert(std::is_base_of<IModel, T>::value, "Field must inherit from IModel");
                    static_assert(!std::is_abstract<T>::value, "T must be non abstract");

                    for (const auto& param: params) {
                        headers_.insert(headers_.end(), param.headers().begin(), param.headers().end());
                        params_.push_back(std::make_unique<T>(param));
                    }
                    return *this;
                }

                Function& statement_add(const std::string& method) & { 
                    body_lines_.push_back(method);
                    return *this;
                }
        };

    }; /* generic */

}; /* syntax */