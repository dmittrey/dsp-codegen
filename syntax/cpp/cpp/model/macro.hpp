#pragma once

#include "generic/model/model.hpp"

#include "generic/clojure.hpp"

#include "rval.hpp"

using stx::gen::Type;

namespace stx {

    namespace cpp {

        struct Macro final : gen::Model {
        public:
            const std::string name;
            std::vector<std::string> params;
            std::optional<std::string> body = std::nullopt; /* cond compilation */

        public:
            Macro(const std::string& name) : name(name) {}

        public:
            Macro& add_clojure(const gen::Clojure<std::string>& cloj) & {
                params.push_back(cloj.param);
                add_body(cloj.body);
                return *this;
            }

            Macro& add_body(const std::string& bod) & {
                if (body.has_value())
                    *body += bod + '\\' + '\n';
                else
                    body = std::optional(bod);
                return *this;
            }

        public:
            std::string code() override {
                std::string res;
                res += "#ifndef " + name + '\n';
                res += "#define " + name;
                if (params.size() != 0) {
                    res += '(';
                    for (const auto& p : params)
                        res += p + ',' + ' ';
                    res.pop_back();
                    res.pop_back();
                    res += ')';
                }
                res += " (" + body.value_or("") + ")" + '\n';
                res += "#endif";
                return res;
            }
        };

    }; /* cpp */

}; /* syntax */