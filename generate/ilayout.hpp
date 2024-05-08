#pragma once

#include <string>
#include <vector>

#include <imodel.hpp>

namespace Generate {

    struct ILayout {
        virtual std::vector<IModel*> models() = 0;
        virtual void add_model(IModel* model) = 0;
        virtual std::string render() const = 0;
        virtual ~ILayout() {};
    };

}; /* Generate */