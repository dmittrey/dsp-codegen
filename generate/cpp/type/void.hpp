#pragma once

#include "interface/type.hpp"

using Utility::Type;

namespace Generate {

    namespace Types {

        namespace Cpp {

            Type make_void() {
                return {"void"};
            }

        }; /* Cpp */

    }; /* Types */

}; /* Generate */