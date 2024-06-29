#pragma once

#include "imodel.hpp"

namespace stx {

    /* Abstraction to group models */
    struct ILayout : IModel {
    public:
        virtual const std::vector<IModel*>& models() const = 0;
        virtual ILayout& add_model(IModel* model) = 0;
    };

}; /* syntax */