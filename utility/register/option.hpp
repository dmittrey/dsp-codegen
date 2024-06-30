#pragma once

#include <string>
#include <iostream>

#include "fixedp.hpp"

namespace util {

    struct Option final {
        std::string name;
        std::string description;
        std::optional<std::string> s_ioctl = std::nullopt;
        std::optional<std::string> g_ioctl = std::nullopt;
        std::pair<uint8_t, uint8_t> bit_range;
        FixedP fixedp;

        uint8_t size() const {
            return bit_range.second - bit_range.first + 1; // [4; 8] = 5bits 
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