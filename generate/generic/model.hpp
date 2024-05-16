#pragma once

#include "interface/imodel.hpp"

#include "interface/type.hpp"

using Utility::Type;

namespace Generate {

    struct Model : IModel {
    protected:
        std::vector<std::string> headers_ = {};
    
    public:
        const std::vector<std::string>& headers() const & override { return headers_; }
    };

    struct Comment : Model {
        const std::string text;

        Comment(const std::string& text) : text(text) {}
    };

    struct RVal : Model {
    public:
        const Type type;
        const std::optional<std::string> name; // Anon structures if possible

    protected:
        RVal(const Type& type, const std::optional<std::string>& name) : type(type), name(name) { 
            if (type.header.has_value())
                headers_.push_back(type.header.value());
        }
    };

    struct Structure : Model {
    protected:
        const std::unique_ptr<RVal> name_;
        std::vector<std::unique_ptr<RVal>> fields_ = {};

    protected:
        Structure(std::unique_ptr<RVal> name) : name_(std::move(name)) {
            const auto& tmp = name_->headers();
            headers_.insert(headers_.end(), tmp.begin(), tmp.end());
        }
    };

    struct Function : public Model {
    protected:
        const std::unique_ptr<RVal> name_;
        std::vector<std::unique_ptr<RVal>> params_ = {};

    public:
        virtual Function& param_add(const RVal& param) = 0;

    protected:
        Function(std::unique_ptr<RVal> name) : name_(std::move(name)) {
            const auto& tmp = name_->headers();
            headers_.insert(headers_.end(), tmp.begin(), tmp.end());
        }
    
    protected:
        virtual const std::string payload() const = 0;
    };

}; /* Generate */