#pragma once

#include "syntax/generic/model/model.hpp"

namespace Generate {

    struct Type final : IModel {
    protected:
        std::vector<std::string> headers_ = {};

    public:
        const std::string name;

    public:
        Type(const std::string& name) :  name(name) {}
        Type(const std::string& name, const std::string& header) :  name(name) { headers_.push_back(header); }

    public:
        const std::vector<std::string>& headers() const & override { return headers_; }
        std::string code() const override { return name; }
    };

}; /* Generate */