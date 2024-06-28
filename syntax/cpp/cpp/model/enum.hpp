#pragma once

#include "generic/model/structure.hpp"

#include "rval.hpp"
#include "cpp/types.hpp"

namespace stx {

    namespace cpp {

        struct Enum final : gen::Structure<std::string> {

        public:
            Enum(const Type &type) : gen::Structure<std::string>(type, std::nullopt) {}

        public:
            std::string code() override {
                std::string str;
                str += type.code() + '{' + '\n';

                for (const auto &field : fields_) {
                    str += '\t' + *field + ',' + '\n';
                }

                str += std::string("}") + ';' + '\n';
                return str;
            };
        };

    }; /* cpp */

}; /* syntax */