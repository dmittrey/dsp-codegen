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
        virtual void add_header(const std::string &name) { headers_.push_back(name); }
    
    public:
        virtual std::string code() = 0;
        operator std::string() {
            return code();
        }

    public:
        virtual ~IModel() {};
    };

}; /* syntax */