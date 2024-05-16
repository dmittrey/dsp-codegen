#pragma once

#include "interface/type.hpp"

using Utility::Type;

namespace Generate {

    namespace Types {

        namespace Cpp {

            Type make_int() {
                return {"int"};
            }

        }; /* Cpp */

    }; /* Types */

}; /* Generate */