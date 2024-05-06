/*
    Share same types with parse and generate modules to compatible interface
*/
#pragma once

#include <string>
#include <vector>

namespace Utility {

    struct Type {
        virtual std::vector<std::string> headers() = 0;
        virtual std::string name() = 0;
        virtual ~Type() {}
    };

}; /* Utility */