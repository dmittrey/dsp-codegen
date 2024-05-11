#pragma once

#include "interface/imodel.hpp"

#include "type.hpp"

using namespace Utility;

namespace Generate {

    struct Model : IModel {
    protected:
        std::vector<std::string> headers_ = {};
    
    public:
        std::vector<std::string> headers() const override { return headers_; }
    };

    struct RVal : Model {
    protected:
        std::shared_ptr<Type> type_;
        std::string name_;

    protected:
        RVal(Type* type, std::string name) : type_(type), name_(name) { 
            headers_.push_back(type->header()); 
        }
    };

    struct Structure : Model {
    protected:
        RVal* name_;
        std::vector<RVal*> fields_ = {};
    
    public:
        virtual Structure& field_add(RVal* field) = 0;

    protected:
        Structure(RVal* name) : name_(name) {
            const auto& tmp = name->headers();
            headers_.insert(headers_.end(), tmp.begin(), tmp.end());
        }
    };

    struct Function : public Model {
    protected:
        RVal* name_;
        std::vector<RVal*> params_ = {};

    public:
        virtual Function& param_add(RVal* param) = 0;

    protected:
        Function(RVal* name) : name_(name) {
            const auto& tmp = name->headers();
            headers_.insert(headers_.end(), tmp.begin(), tmp.end());
        }
    };

}; /* Generate */