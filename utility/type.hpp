/*
    Share same types with parse and generate modules to compatible interface
*/
#pragma once

#include <string>
#include <vector>

namespace Utility {

    struct Type {
        virtual std::string header() const = 0;
        virtual std::string name() const = 0;
        virtual ~Type() {}
    };

}; /* Utility */