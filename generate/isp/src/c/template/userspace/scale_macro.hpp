#pragma once

#include "util.hpp"

#include "c/model/macro.hpp"

namespace gen {

    namespace c {

        namespace tmplt {

            stx::c::Macro* ScaleMacro() {
                auto scale_macro = new stx::c::Macro(tmplt::ScaleMacroName);
                scale_macro->params_set<RVal>({{t::Empty(), "frac_bits"}});
                scale_macro->statement_add("1 << frac_bits");
                return scale_macro;
            };
            
        }; /* template */

    }; /* c */

}; /* generate */