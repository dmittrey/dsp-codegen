#pragma once

#include "syntax/interface/type.hpp"

namespace Generate {

    namespace Cpp {

        namespace Types {

            Type make_struct() {
                return {"struct"};
            }

        }; /* Types */

    }; /* Cpp */

}; /* Generate */