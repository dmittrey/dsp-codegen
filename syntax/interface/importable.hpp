#pragma once

#include <vector>
#include <string>

namespace stx {

    struct Importable {
    private:
        std::vector<std::string> headers_ = {};

    public:
        const std::vector<std::string>& headers() const & { return headers_; } // Const prevent edit in consumer
        void push_header(const std::string& header) { headers_.push_back(header); }
        void add_headers(const std::vector<std::string> &headers) { 
            headers_.insert(headers_.end(), headers.begin(), headers.end());

            std::sort(headers_.begin(), headers_.end());
            headers_.erase(std::unique(headers_.begin(), headers_.end()), headers_.end());
        }

    public:
        virtual ~Importable() {};
    };

}; /* syntax */