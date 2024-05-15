#pragma once

#include "type.hpp"

namespace Utility {

    struct Void final : Type {
        Void() : Type("void") { }
    };

}; /* Utility */