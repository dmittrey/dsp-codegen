#pragma once

#include "generic/structure.hpp"

#include "rval.hpp"

namespace Generate {

    struct CppStructure final : Structure {
    private:
        uint64_t size_;

    public:
        CppStructure(const Type &type, const std::optional<std::string> &name) : Structure(type, name) {}

        uint64_t size() { return size_; }

        using Structure::field_add;
        CppStructure& field_add(const CppRVal& field) & {
            Structure::field_add(std::make_unique<CppRVal>(field));
            size_ += field.size();
            return *this;
        }

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

}; /* Generate */