#pragma once

/* Header for extra language entities */

#include "structure.hpp"

#include "type/type.hpp"

using namespace Generate::Cpp;

namespace Generate {

    namespace Cpp {

        CppStructure* make_anon_enum() {
            return new CppStructure{Types::make_enum(), std::nullopt};
        }

    }; /* Cpp */

}; /* Generate */