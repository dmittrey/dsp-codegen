#pragma once

#include <iostream>
#include <string>

#include "format.hpp"
#include "type/uint.hpp"

namespace Utility {

    struct Register {
        std::string name;
        std::vector<std::pair<Type*, std::string>> fields;
    };

}; /* Utility */