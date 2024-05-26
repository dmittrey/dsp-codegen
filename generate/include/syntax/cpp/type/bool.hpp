#pragma once

#include "syntax/interface/type.hpp"

namespace Generate {

    namespace Cpp {

        namespace Types {

            Type make_bool() {
                return {"bool"};
            }

        }; /* Types */

    }; /* Cpp */

}; /* Generate */