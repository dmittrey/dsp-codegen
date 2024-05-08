#pragma once

#include "interface/imodel.hpp"

#include "type.hpp"

using namespace Utility;

namespace Generate {

    struct Model : IModel {
    protected:
        std::vector<std::string> headers_ = {};
    
    public:
        std::vector<std::string> headers() override { return headers_; }
    };

    struct RVal : Model {
    protected:
        Type* type_;
        std::string name_;

    public:
        RVal() = delete;
        RVal(RVal&& arg) = delete; /* Constraints to save headers_ invariant */
        RVal(Type* type, std::string name) : type_(type), name_(name) { 
            headers_.push_back(type->header()); 
        }
    };

    struct Structure : Model {
    protected:
        RVal* name_;
        std::vector<RVal*> fields_ = {};

    public:
        Structure() = delete;
        Structure(Structure&& arg) = delete; /* Constraints to save headers_ invariant */
        Structure(RVal* name) : name_(name) {
            const auto& tmp = name->headers();
            headers_.insert(headers_.end(), tmp.begin(), tmp.end());
        }

        virtual void field_add(RVal* field) = 0;
    };

    struct Function : public Model {
    protected:
        RVal* name_;
        std::vector<RVal*> params_ = {};

    public:
        Function() = delete;
        Function(Function&& arg) = delete; /* Constraints to save headers_ invariant */
        Function(RVal* name) : name_(name) {
            auto tmp = name->headers();
            headers_.insert(headers_.end(), tmp.begin(), tmp.end());
        }

        virtual void param_add(RVal* param) = 0;
    };

}; /* Generate */