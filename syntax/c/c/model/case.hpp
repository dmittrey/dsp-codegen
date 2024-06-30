#pragma once

#include "generic/model/structure.hpp"

#include "c/types.hpp"
#include "rval.hpp"

namespace stx {

    namespace c {

        struct Case final : gen::Structure<std::string> {

        public:
            Case(const std::string &name) : gen::Structure<std::string>(Type("case"), name) {}

        public:
            using gen::Structure<std::string>::name;
            using gen::Structure<std::string>::field_add;

        public:
            std::string code() const override {
                std::string str;
                str += type.name + ' ' + name.value_or("") + ':' + '\n';

                for (const auto &field : fields_) {
                    str += '\t' + *field + ';' + '\n';
                }

                return str;
            };
        };

    }; /* c */

}; /* syntax */