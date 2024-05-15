#pragma once

#include "interface/imodel.hpp"

#include "type/type.hpp"

using namespace Utility;

namespace Generate {

    struct Model : IModel {
    protected:
        std::vector<std::string> headers_ = {};
    
    public:
        const std::vector<std::string>& headers() const & override { return headers_; }
    };

    struct RVal : Model {
    protected:
        std::unique_ptr<Type> type_;
        std::string name_;

    protected:
        RVal(const RVal& obj) : RVal(*obj.type_, obj.name_) {} 
        RVal(const Type& type, const std::string& name) : type_(std::make_unique<Type>(type)), name_(name) { 
            if (type_->header.has_value())
                headers_.push_back(type_->header.value());
        }
    };

    struct Decl : Model {
    protected:
        std::unique_ptr<RVal> name_;

    protected:
        Decl(std::unique_ptr<RVal> name) : name_(std::move(name)) { }
    };

    struct Structure : Model {
    protected:
        std::unique_ptr<RVal> name_;
        std::vector<std::unique_ptr<RVal>> fields_ = {};
    
    public:
        virtual Structure& field_add(const RVal& field) = 0;

    protected:
        Structure(std::unique_ptr<RVal> name) : name_(std::move(name)) {
            const auto& tmp = name_->headers();
            headers_.insert(headers_.end(), tmp.begin(), tmp.end());
        }
    };

    struct Function : public Model {
    protected:
        std::unique_ptr<RVal> name_;
        std::vector<std::unique_ptr<RVal>> params_ = {};

    public:
        virtual Function& param_add(const RVal& param) = 0;

    protected:
        Function(std::unique_ptr<RVal> name) : name_(std::move(name)) {
            const auto& tmp = name_->headers();
            headers_.insert(headers_.end(), tmp.begin(), tmp.end());
        }
    };

}; /* Generate */