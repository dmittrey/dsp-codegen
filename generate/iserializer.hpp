#pragma once

#include "layout.hpp"

/* RAII for render layouts */

namespace Generate {

    struct ISerializer {
        virtual void serialize(const Layout& layout) = 0;
        virtual ~ISerializer() {};
    };

}; /* Generate */