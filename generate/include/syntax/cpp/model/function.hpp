#pragma once

#include "syntax/generic/model/function.hpp"

namespace Generate {

    struct CppFunction : Function {
    public:
        CppFunction(const Type &type, const std::string &name) : Function(type, name) {}

    public:
        std::string code() const override {
            std::string str;
            str += type.code() + ' ' + name + '(';

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