#pragma once

#include "generic/model/function.hpp"

namespace stx {

    namespace cpp {

    struct Function : gen::Function {
    public:
        Function(const Type &ret_type, const std::string &name) : gen::Function(ret_type, name) {}

    public:
        const std::string payload() const override {
            std::string res;
            for (const auto& s : body_lines_) {
                res += "\t" + s + ";\n";
            }
            return res;
        };

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
            str += payload();
            str += std::string("}") + ';' + '\n';
            return str;
        };
    };

    }; /* cpp */

}; /* syntax */