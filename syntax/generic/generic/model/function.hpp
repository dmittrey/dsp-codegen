#pragma once

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

                template<typename T>
                Function& param_add(const T& param) & { 
                    static_assert(std::is_base_of<IModel, T>::value, "Field must inherit from IModel");
                    static_assert(!std::is_abstract<T>::value, "T must be non abstract");

                    headers_.insert(headers_.end(), param.headers().begin(), param.headers().end());
                    params_.push_back(std::make_unique<T>(param));
                    return *this;
                }

                template<typename T>
                Function& clojure_add(const Clojure<T>& cloj) & { 
                    param_add<T>(cloj.param);
                    body_lines_.push_back(cloj.body); 
                    return *this;
                }
        };

    }; /* generic */

}; /* syntax */