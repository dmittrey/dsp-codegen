#pragma once

#include <vector>
#include <string>

namespace stx {

    /* Rendering object */
    struct IModel {
    protected:
        std::vector<std::string> headers_ = {};

    public:
        virtual const std::vector<std::string>& headers() const & { return headers_; } // Const prevent edit in consumer
        virtual std::string code() = 0;
        virtual ~IModel() {};

    public:
        operator std::string() {
            return code();
        }
    };

}; /* syntax */