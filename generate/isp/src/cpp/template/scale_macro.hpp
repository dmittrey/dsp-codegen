#pragma once

#include "util.hpp"

#include "cpp/model/macro.hpp"

namespace gen {

    namespace cpp {

        namespace tmplt {

            stx::cpp::Macro* ScaleMacro() {
                auto scale_macro = new stx::cpp::Macro(tmplt::ScaleMacroName);
                scale_macro->add_clojure({"frac_bits", "1 << frac_bits"});
                return scale_macro;
            };
            
        }; /* template */

    }; /* c++ */

}; /* generate */