#pragma once

#include "imodel.hpp"

#include "type.hpp"

using namespace Utility;

namespace Generate {

    struct Model : IModel {
    protected:
        std::vector<std::string> headers_ = {};
    
    public:
        std::vector<std::string> headers() override { return headers_; }
    };

    struct RVal final : Model {
    private:
        Type *type_;
        std::string name_;

    public:
        RVal(Type* type, std::string name) : type_(type), name_(name) { 
            headers_.push_back(type->header()); 
        }

        std::string code() const override {
            return type_->name() + " " + name_;
        }
    };

    struct Structure final : Model {
    private:
        RVal name_;
        std::vector<RVal> fields_;

    public:
        Structure(RVal name, std::vector<RVal> fields) : name_(name), fields_(fields) {
            headers_.insert(headers_.end(), name.headers_.begin(), name.headers_.end());

            for (auto field : fields_)
                headers_.insert(headers_.end(), field.headers_.begin(), field.headers_.end());
        }

        std::string code() const override {
            std::string str;
            str += name_.code() + ' ' + '{' + '\n';

            for (auto field : fields_) {
                str += '\t' + field.code() + ';' + '\n';
            }

            str += std::string("}") + ';' + '\n';
            return str;
        }
    };

    struct Function final : Model {
    private:
        RVal name_;
        std::vector<RVal> params_;

    public:
        Function(RVal name, std::vector<RVal> params) : name_(name), params_(params) {
            for (auto header : name.headers())
                headers_.push_back(header);

            for (auto param: params_)
                for (auto header : param.headers())
                    headers_.push_back(header);
        }

        std::string code() const override {
            std::string str;
            str += name_.code() + '(' + '\n';

            for (auto param : params_) {
                str += '\t' + param.code() + ',' + ' ';
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