#pragma once

#include "ilayout.hpp"

/* RAII for render layouts */

namespace Generate {

    struct ISerializer {
        virtual void serialize(const ILayout& layout) const = 0;
        virtual ~ISerializer() {};
    };

}; /* Generate */