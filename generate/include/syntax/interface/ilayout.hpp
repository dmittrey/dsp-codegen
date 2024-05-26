#pragma once

#include "imodel.hpp"

namespace Generate {

    /* Abstraction to group models */
    struct ILayout {
        virtual std::vector<IModel*> models() const = 0;
        virtual ILayout& add_model(IModel* model) = 0;
        virtual std::string render() = 0;
        virtual ~ILayout() {};
    };

}; /* Generate */