#pragma once

#include "ilayout.hpp"

/* RAII for render layouts */

namespace Generate {

    struct ISerializer {
        virtual void serialize(const ILayout& layout) = 0;
        virtual ~ISerializer() {};
    };

}; /* Generate */