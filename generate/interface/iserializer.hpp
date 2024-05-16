#pragma once

#include "ilayout.hpp"

namespace Generate {

    /* Abstraction to render layouts */
    struct ISerializer {
        virtual void serialize(ILayout& layout) const = 0;
        virtual ~ISerializer() {};
    };

}; /* Generate */