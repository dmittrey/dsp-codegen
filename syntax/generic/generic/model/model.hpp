#pragma once

#include "imodel.hpp"

namespace stx {

    namespace gen {

        struct Model : IModel {
        protected:
            std::vector<std::string> headers_ = {};
        
        public:
            const std::vector<std::string>& headers() const & override { return headers_; } // Const prevent edit in consumer
        };

    }; /* generic */

}; /* syntax */