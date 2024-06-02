#pragma once

#include "model.hpp"

namespace Syntax {

    struct Function : Model {
        public:
            const Type type;
            const std::string name;
        protected:
            std::vector<std::unique_ptr<IModel>> params_ = {}; /* Nested strutures, Comments */

        protected:
            Function(const Type &type, const std::string &name) : type(type), name(name) {}

            Function& param_add(std::unique_ptr<IModel> param) & {
                headers_.insert(headers_.end(), param->headers().begin(), param->headers().end());
                params_.emplace_back(std::move(param)); 
                return *this;
            }

        protected:
            virtual const std::string payload() const = 0;
    };

}; /* Syntax */