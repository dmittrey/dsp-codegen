#pragma once

#include "model.hpp"

namespace Generate {

    struct RVal : Model {
    public:
        const Type type;
        const std::string name;

    protected:
        RVal(const Type& type, const std::string& name) : type(type), name(name) { 
            headers_.insert(headers_.end(), type.headers().begin(), type.headers().end());
        }
    };

}; /* Generate */