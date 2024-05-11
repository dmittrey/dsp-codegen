#pragma once

#include "generic/model.hpp"

namespace Generate {

    struct CppRVal final : RVal {
        CppRVal(std::shared_ptr<Type> type, std::string name) : RVal(type, name) {}
        CppRVal(const RVal& obj) : RVal(obj) {}

        std::string code() const override {
            return type_->name() + " " + name_;
        }
    };

    struct CppStructure final : Structure {
        CppStructure(const CppRVal& name) : Structure(std::make_unique<CppRVal>(name)) {}

        CppStructure& field_add(const RVal& field) override {
            const auto& tmp = field.headers();
            headers_.insert(headers_.end(), tmp.begin(), tmp.end());

            fields_.push_back(std::make_unique<CppRVal>(field));
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

    struct CppFunction final : Function {
        CppFunction(const CppRVal& name) : Function(std::make_unique<CppRVal>(name)) {}

        CppFunction& param_add(const RVal& param) override {
            const auto& tmp = param.headers();
            headers_.insert(headers_.end(), tmp.begin(), tmp.end());

            params_.push_back(std::make_unique<CppRVal>(param));
            return *this;
        };

        std::string code() const override {
            std::string str;
            str += name_->code() + '(' + '\n';

            for (const auto &param : params_) {
                str += '\t' + param->code() + ',' + ' ';
            }
            str.pop_back();
            str.pop_back(); // Remove last ", "

            str += std::string(")") + '{' + '\n';
            //Payload
            str += std::string("}") + ';';
            return str;
        };
    };

}; /* Generate */