#pragma once

#include "generic/model.hpp"

namespace Generate {

    struct CppRVal : RVal {
        CppRVal(const RVal& obj) : RVal(obj) {}
        CppRVal(const Type& type, const std::optional<std::string>& name) : RVal(type, name) {}

        std::string code() const override {
            return type.name + (name.has_value() ? " " + name.value() : "");
        }
    };

    struct CppComment : Comment {
        CppComment(const std::string& text) : Comment(text) {}

        std::string code() const override {
            return "/* " + text + " */";
        }
    };

    struct CppStructure final : Structure {
        uint64_t size;
        
        struct Field final : CppRVal {
            std::optional<uint64_t> size;

            // Field(const RVal& obj) : CppRVal(obj) {}
            Field(const Type& type, const std::optional<std::string>& name, 
                    std::optional<uint64_t> size) : CppRVal(type, name), size(size) {}
            Field(const Type& type, const std::optional<std::string>& name) :
                    Field(type, name, std::nullopt) {}

            std::string code() const override {
                return type.name 
                        + (name.has_value() ? " " + name.value() : "") 
                        + (size.has_value() ? ':' + std::to_string(size.value()) : "");
            }   
        };

        CppStructure(const CppRVal& name) : Structure(std::make_unique<CppRVal>(name)) {}

        CppStructure& field_add(const Field& field) {
            const auto& tmp = field.headers();
            headers_.insert(headers_.end(), tmp.begin(), tmp.end());

            fields_.push_back(std::make_unique<Field>(field));
            size += field.size.value_or(0);
            return *this;
        };

        std::string code() const override {
            std::string str;
            str += name_->code() + ' ' + '{' + '\n';

            for (const auto &field : fields_) {
                str += '\t' + field->code() + ';' + '\n';
            }

            str += std::string("}") + ';' + '\n';
            return str;
        };
    };

    struct CppFunction : Function {
        CppFunction(const CppRVal& name) : Function(std::make_unique<CppRVal>(name)) {}

        CppFunction& param_add(const RVal& param) override {
            const auto& tmp = param.headers();
            headers_.insert(headers_.end(), tmp.begin(), tmp.end());

            params_.push_back(std::make_unique<CppRVal>(param));
            return *this;
        };

        std::string code() const override {
            std::string str;
            str += name_->code() + '(';

            if (params_.size()) {
                for (const auto &param : params_) {
                    str += param->code() + ',' + ' ';
                }
                str.pop_back();
                str.pop_back(); // Remove last ", "
            }

            str += std::string(")") + '{' + '\n';
            str += '\t' + payload();
            str += std::string("}") + ';' + '\n';
            return str;
        };
    };

}; /* Generate */