#pragma once

#include "type.hpp"

namespace Utility {

    struct Struct final : Type {
        Struct() : Type("struct", "") { }
    };

}; /* Utility */