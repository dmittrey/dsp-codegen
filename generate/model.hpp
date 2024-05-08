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
        std::shared_ptr<Type> type_;
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
            auto tmp = name.headers();
            headers_.insert(headers_.end(), tmp.begin(), tmp.end());

            for (auto field : fields_) {
                tmp = field.headers();
                headers_.insert(headers_.end(), tmp.begin(), tmp.end());
            }
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

    struct Function final : public Model {
    private:
        RVal name_;
        std::vector<RVal> params_;

    public:
        Function(RVal name, std::vector<RVal> params) : name_(name), params_(params) {
            auto tmp = name.headers();
            headers_.insert(headers_.end(), tmp.begin(), tmp.end());

            for (auto param : params_) {
                tmp = param.headers();
                headers_.insert(headers_.end(), tmp.begin(), tmp.end());
            }
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