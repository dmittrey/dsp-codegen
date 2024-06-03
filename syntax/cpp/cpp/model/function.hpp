#pragma once

#include "generic/model/function.hpp"

namespace stx {

    namespace cpp {

    struct Function : gen::Function {
    public:
        Function(const Type &type, const std::string &name) : gen::Function(type, name) {}

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

    }; /* cpp */

}; /* syntax */