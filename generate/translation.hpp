/*
    Structure to describe translation unit
*/
#pragma once

#include <vector>
#include <string>

#include "type.hpp"
#include "operation.hpp"

using namespace Utility;
using namespace Generate;

namespace Generate {

    struct Function {
        Uint8 ret_type;
        std::vector<std::pair<Uint8, std::string>> arg_list;
        std::string name;
        Getter op;
    };

}; /* Generate */