#pragma once

#include "syntax/interface/type.hpp"

namespace Generate {

    namespace Cpp {

        namespace Types {

            Type make_void() {
                return {"void"};
            }

        }; /* Types */

    }; /* Cpp */

}; /* Generate */