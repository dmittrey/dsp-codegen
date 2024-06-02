#pragma once

#include "interface/ilayout.hpp"

namespace Serialize {

    /* Abstraction to render layouts */
    struct ISerializer {
        virtual void serialize(Syntax::ILayout& layout) const = 0;
        virtual ~ISerializer() {};
    };

}; /* Serialize */