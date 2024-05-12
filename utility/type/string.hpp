#pragma once

#include "type.hpp"

namespace Utility {

    struct String final : Type {
        String() : Type("std::string", "string") { }
    };

}; /* Utility */