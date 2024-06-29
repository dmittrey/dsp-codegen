#pragma once

#include "generic/model.hpp"

namespace stx {

    namespace gen {

        struct RVal : Model {
        public:
            const Type type;
            const std::string name;
    
        protected:
            RVal(const Type& type, const std::string& name) : type(type), name(name) { 
                add_headers(type.headers());
            }
        };

    }; /* generic*/

}; /* syntax */