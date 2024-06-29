#pragma once

#include "generic/model.hpp"
#include "type.hpp"

namespace stx {

    namespace gen {

        struct Function : Model {
            public:
                const Type type;
                const std::string name;
            protected:
                std::vector<std::unique_ptr<Model>> params_ = {}; /* Nested strutures, Comments */
                std::vector<std::string> body_lines_ = {};

            public:
                Function(const Type &type, const std::string &name) : type(type), name(name) {}

            public:
                template<typename T>
                Function& params_set(std::initializer_list<T> params) & { 
                    for (const auto& param: params) {
                        const auto& tmp_vec = param.headers();
                        add_headers(tmp_vec);

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