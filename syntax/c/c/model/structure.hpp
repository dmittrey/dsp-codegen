#pragma once

#include "generic/model/structure.hpp"

#include "rval.hpp"

namespace stx {

    namespace c {

        struct Structure final : gen::Structure<gen::Model> {
        private:
            uint64_t size_;

        public:
            Structure(const Type &type, const std::optional<std::string> &name) : gen::Structure<gen::Model>(type, name) {}
        
        public:
            using gen::Structure<gen::Model>::field_add;

        public:
            Structure& field_add(const RVal& field) & {
                gen::Structure<gen::Model>::field_add<RVal>(field);
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

    }; /* c */

}; /* syntax */