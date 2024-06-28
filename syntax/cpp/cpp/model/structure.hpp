#pragma once

#include "generic/model/structure.hpp"

#include "rval.hpp"

namespace stx {

    namespace cpp {

        struct Structure final : gen::Structure<IModel> {
        private:
            uint64_t size_;

        public:
            Structure(const Type &type, const std::optional<std::string> &name) : gen::Structure<IModel>(type, name) {}

            using gen::Structure<IModel>::field_add; // Add parent method to use for IModel

            Structure& field_add(const RVal& field) & {
                gen::Structure<IModel>::field_add<RVal>(field);
                size_ += field.size;
                return *this;
            }
            uint64_t size() { return size_; }

        public:
            std::string code() override {
                std::string str;
                str += type.code() + ' ' + name.value_or("") + '{' + '\n';

                for (const auto &field : fields_) {
                    str += '\t' + field->code() + ';' + '\n';
                }

                str += std::string("}") + ';' + '\n';
                return str;
            };
        };

    }; /* cpp */

}; /* syntax */