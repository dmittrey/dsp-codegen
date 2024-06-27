#pragma once

#include "generic/model/function.hpp"

namespace stx {

    namespace cpp {

    struct Function : gen::Function {
    public:
        Function(const Type &ret_type, const std::string &name) : gen::Function(ret_type, name) {}

    public:
        std::string code() override {
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
            for (const auto& s : body_lines_) {
                str += "\t" + s + ";\n";
            }
            str += std::string("}") + ';' + '\n';
            return str;
        };
    };

    }; /* cpp */

}; /* syntax */