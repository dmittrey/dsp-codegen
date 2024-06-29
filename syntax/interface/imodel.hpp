#pragma once

#include <vector>
#include <string>

#include "importable.hpp"

namespace stx {

    /* Rendering object */
    struct IModel : Importable {
    public:
        virtual std::string code() const = 0;
    
    public:
        operator std::string() const { return code(); }

    public:
        virtual ~IModel() {};
    };

}; /* syntax */