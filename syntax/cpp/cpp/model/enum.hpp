#pragma once

#include "generic/model/structure.hpp"

#include "rval.hpp"
#include "cpp/types.hpp"

namespace stx {

    namespace cpp {

        struct Enum final : gen::Structure {

        public:
            Enum(const Type &type) : gen::Structure(type, std::nullopt) {}

            using gen::Structure::field_add; // Add parent method to use for IModel

        public:
            std::string code() override {
                std::string str;
                str += type.code() + '{' + '\n';

                for (const auto &field : fields_) {
                    str += '\t' + field->code() + ',' + '\n';
                }

                str += std::string("}") + ';' + '\n';
                return str;
            };
        };

    }; /* cpp */

}; /* syntax */