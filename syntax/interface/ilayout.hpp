#pragma once

#include "imodel.hpp"

namespace stx {

    /* Abstraction to group models */
    struct ILayout : IModel {
        virtual const std::vector<IModel*>& models() const = 0;
        virtual ILayout& add_model(IModel* model) = 0;
        virtual void add_header(const std::string &name) { headers_.push_back(name); }
        virtual ~ILayout() {};
    };

}; /* syntax */