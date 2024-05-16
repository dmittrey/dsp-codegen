#pragma once

#include "interface/type.hpp"

using Utility::Type;

namespace Generate {

    namespace Types {

        namespace Cpp {

            Type make_bool() {
                return {"bool"};
            }

        }; /* Cpp */

    }; /* Types */

}; /* Generate */