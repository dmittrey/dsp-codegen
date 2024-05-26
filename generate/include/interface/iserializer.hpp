#pragma once

#include "ilayout.hpp"

namespace Generate {

    /* Abstraction to render layouts */
    struct ISerializer {
        virtual void serialize(ILayout& layout) const = 0;
        virtual ~ISerializer() {};
    };

    std::unique_ptr<ISerializer> make_file_serializer(const std::string& fname);

}; /* Generate */