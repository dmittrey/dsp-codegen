#pragma once

/* Header for extra language entities */

#include "model/enum.hpp"

#include "types.hpp"

namespace stx {

    namespace cpp {

        Enum* make_anon_enum() {
            return new Enum(t::Enum());
        }

    }; /* cpp */

}; /* syntax */