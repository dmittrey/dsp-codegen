#pragma once

#include "util.hpp"

#include "cpp/model/macro.hpp"

namespace gen {

    namespace cpp {

        namespace tmplt {

            stx::cpp::Macro* ScaleMacro() {
                auto scale_macro = new stx::cpp::Macro(tmplt::ScaleMacroName);
                scale_macro->params_set<RVal>({{t::Empty(), "frac_bits"}});
                scale_macro->statement_add("1 << frac_bits");
                return scale_macro;
            };
            
        }; /* template */

    }; /* c++ */

}; /* generate */