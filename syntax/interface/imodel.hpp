#pragma once

#include <vector>
#include <string>

#include "importable.hpp"

namespace stx {

    /* Rendering object */
    struct IModel : Importable {
    public:
        virtual std::string code() const = 0;
        operator std::string() {
            return code();
        }

    public:
        virtual ~IModel() {};
    };

}; /* syntax */