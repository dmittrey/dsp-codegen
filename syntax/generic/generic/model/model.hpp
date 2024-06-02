#pragma once

#include "imodel.hpp"

/* Move generic syntax entities to separate headers to not leak strctures and !work with IModel only! */

namespace Syntax {

    struct Model : IModel {
    protected:
        std::vector<std::string> headers_ = {};
    
    public:
        const std::vector<std::string>& headers() const & override { return headers_; } // Const prevent edit in consumer
    };

}; /* Syntax */