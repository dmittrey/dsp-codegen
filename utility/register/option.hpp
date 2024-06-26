#pragma once

#include <string>
#include <iostream>

#include "fixedp.hpp"

namespace util {

    struct Option final {
        std::string name;
        std::string description;
        std::pair<uint8_t, uint8_t> bit_range;
        FixedP fixedp;

        uint8_t hw_size() const {
            return bit_range.second - bit_range.first + 1; // [4; 8] = 5bits 
        }

        uint8_t log_size() const {
            return fixedp.int_bits + fixedp.fract_bits;
        }

        Format format() const {
            return fixedp.format;
        }

        bool is_float_point() const {
            return fixedp.format != HEX_UNSIGNED && fixedp.format != HEX_SIGNED;
        }

        void dump() const {
            std::cout << "Option:" << "\n"
                << "\t\t" << "name: " << name << "\n"
                << "\t\t" << "description: " << description << "\n"
                << "\t\t" << "bit_range: [" << bit_range.first << ", " << bit_range.second << "]" << "\n"
                << "\t\t" << "val format: " << fixedp.str()
                << std::endl;
        }
    };

}; /* utility */