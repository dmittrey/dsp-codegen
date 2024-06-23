#pragma once

#include "ilayout.hpp"

namespace serialize {

    /* Abstraction to render layouts */
    struct ISerializer {
        virtual void serialize(stx::ILayout& layout) const = 0;
        virtual ~ISerializer() {};
    };

}; /* serialize */