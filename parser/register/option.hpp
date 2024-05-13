#pragma once

#include <string>
#include <utility>
#include <iostream>

#include "rwmode.hpp"
#include "format.hpp"

namespace Parser {

    struct Option {
        std::string name;
        std::string desc;
        std::pair<uint64_t, uint64_t> bit_range;
        RWMode rw_mode;
        Format format;

        void dump() const {
            std::cout << "Option:" << "\n"
                << "\t\t" << "name: " << name << "\n"
                << "\t\t" << "desc: " << desc << "\n"
                << "\t\t" << "bit_range: [" << bit_range.first << ", " << bit_range.second << "]" << "\n"
                << "\t\t" << "rw_mode: " << rw_mode << "\n" 
                << "\t\t" << "format: " << format << std::endl;
        }
    };

}; /* Parser */