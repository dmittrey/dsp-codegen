#pragma once

#include <string>

namespace stx {

    namespace gen {

        template<typename T>
        struct Clojure final {
        public:
            const T param;
            const std::string body;
    
        public:
            Clojure(const T& param, const std::string& body) : param(param), body(body) {}
        };

    }; /* generic*/

}; /* syntax */