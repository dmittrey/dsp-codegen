#pragma once

#include "generic/layout.hpp"

namespace Generate {

    struct CppLayout final : Layout {
        std::string render() override {
            std::string res;
            prepare();
            res += std::string("// Headers\n");
            for (auto header : headers_)
                res += "#include <" + header + '>' + '\n';

            res += std::string("// Models\n");
            for (auto model : models_)
                res += model->code() + '\n';
            
            return res;
        };
    };
};