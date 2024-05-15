#pragma once

#include "interface/type.hpp"

using Utility::Type;

namespace Generate {

    namespace Types {

        Type make_void() {
            return {"void"};
        }

    }; /* Types */

}; /* Generate */