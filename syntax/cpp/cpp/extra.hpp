#pragma once

/* Header for extra language entities */

#include "model/structure.hpp"

#include "types.hpp"

namespace stx {

    namespace cpp {

        Structure* make_anon_enum() {
            return new Structure{t::make_enum(), std::nullopt};
        }

    }; /* cpp */

}; /* syntax */