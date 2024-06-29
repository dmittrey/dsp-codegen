#pragma once

#include "generic/model/model.hpp"

#include "rval.hpp"

using stx::gen::Type;

namespace stx {

    namespace c {

        struct Macro final : gen::Function {
        public:
            Macro(const std::string& name) : gen::Function(t::Empty(), name) {}

        public:
            std::string code() const override {
                std::string res;
                res += "#ifndef " + name + '\n';
                res += "#define " + name;
                if (params_.size() != 0) {
                    res += '(';
                    for (const auto& p : params_)
                        res += p->code() + ',' + ' ';
                    res.pop_back();
                    res.pop_back();
                    res += ')';
                }
                res += " (";
                for (const auto& b : body_lines_)
                    res += b;
                res +=  ")\n";
                res += "#endif";
                return res;
            }
        };

    }; /* c */

}; /* syntax */