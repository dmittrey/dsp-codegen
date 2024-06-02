#pragma once

/* Header for extra language entities */

#include "model/structure.hpp"

#include "types.hpp"

using namespace Syntax::Cpp;

namespace Syntax {

    namespace Cpp {

        CppStructure* make_anon_enum() {
            return new CppStructure{Types::make_enum(), std::nullopt};
        }

    }; /* Cpp */

}; /* Syntax */