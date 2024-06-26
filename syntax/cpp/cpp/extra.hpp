#pragma once

/* Header for extra language entities */

#include "model/structure.hpp"

#include "types.hpp"

namespace stx {

    namespace cpp {

        Structure* make_anon_enum() {
            return new Structure{t::Enum(), std::nullopt};
        }

    }; /* cpp */

}; /* syntax */