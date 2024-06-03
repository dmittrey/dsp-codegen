#pragma once

#include "generic/model/structure.hpp"

#include "rval.hpp"

namespace stx {

    namespace cpp {

        struct Structure final : gen::Structure {
        private:
            uint64_t size_;

        public:
            Structure(const Type &type, const std::optional<std::string> &name) : gen::Structure(type, name) {}

            using gen::Structure::field_add; // Add parent method to use for IModel

            Structure& field_add(const RVal& field) & {
                gen::Structure::field_add<RVal>(field);
                size_ += field.size;
                return *this;
            }
            uint64_t size() { return size_; }

        public:
            std::string code() const override {
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