#pragma once

#include "syntax/interface/type.hpp"

namespace Generate {

    namespace Cpp {

        namespace Types {

            Type make_enum() {
                return {"enum"};
            }

        }; /* Types */

    }; /* Cpp */

}; /* Generate */