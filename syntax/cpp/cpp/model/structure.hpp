#pragma once

#include "generic/model/structure.hpp"

#include "rval.hpp"

namespace Syntax {

    struct CppStructure final : Structure {
    private:
        uint64_t size_;

    public:
        CppStructure(const Type &type, const std::optional<std::string> &name) : Structure(type, name) {}

        using Structure::field_add; // Add parent method to use for IModel

        CppStructure& field_add(const CppRVal& field) & {
            Structure::field_add<CppRVal>(field);
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

}; /* Syntax */