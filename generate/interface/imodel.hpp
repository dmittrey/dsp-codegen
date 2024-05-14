#pragma once

#include <vector>
#include <string>

namespace Generate {

    struct IModel {
        virtual std::vector<std::string>& headers() const & = 0;
        virtual std::string code() const = 0;
        virtual ~IModel() {};
    };

}; /* Generate */