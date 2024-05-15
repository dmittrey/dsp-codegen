#pragma once

#include "type.hpp"

namespace Utility {

    struct Bool final : Type {
        Bool() : Type("bool") { }
    };

}; /* Utility */