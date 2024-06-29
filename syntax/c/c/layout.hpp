#pragma once

#include "generic/layout.hpp"

namespace stx {

    namespace c {

        struct Layout final : gen::Layout {
            std::string code() const override {
                std::string res;
                /* Headers */
                for (auto header : headers())
                    res += "#include \"" + header + '\"' + '\n';

                /* Models */
                for (auto model : models_)
                    res += model->code() + '\n';

                return res;
            };
        };

    }; /* c */

}; /* syntax */