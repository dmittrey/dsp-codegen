#pragma once

#include <string>

#include "type.hpp"

using namespace Utility;

namespace Generate {

    struct Model {
        virtual std::string render() = 0;
        virtual ~Model() {};
    };

    struct RVal final : Model {
        Type *type;
        std::string name;

        std::string render() override {
            return type->name() + " " + name;
        }
    };

    struct Structure final : Model {
        RVal name;
        std::vector<RVal> fields;

        std::string render() override {
            std::string str;
            str += name.render() + ' ' + '{' + '\n';

            for (auto field : fields) {
                str += '\t' + field.render() + ';' + '\n';
            }

            str += std::string("}") + ';' + '\n';
            return str;
        }
    };

    struct Function final : Model {
        RVal name;
        std::vector<RVal> params;

        std::string render() override {
            std::string str;
            str += name.render() + '(' + '\n';

            for (auto param : params) {
                str += '\t' + param.render() + ',' + ' ';
            }
            str.pop_back();
            str.pop_back(); // Remove last ", "

            str += std::string(")") + '{' + '\n';
            //Payload
            str += std::string("}") + ';';
            return str;
        }
    };

}; /* Generate */