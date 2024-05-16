#pragma once

#include <string>
#include <iostream>

#include "format.hpp"

namespace Utility {

    struct Option final {
        std::string name;
        std::string description;
        std::pair<uint64_t, uint64_t> bit_range;
        Format format;

        uint64_t size() const {
            return bit_range.second - bit_range.first + 1; // [4; 8] = 5bits 
        }

        void dump() const {
            std::cout << "Option:" << "\n"
                << "\t\t" << "name: " << name << "\n"
                << "\t\t" << "description: " << description << "\n"
                << "\t\t" << "bit_range: [" << bit_range.first << ", " << bit_range.second << "]" << "\n"
                << "\t\t" << "format: " << format << std::endl;
        }
    };

}; /* Utility */