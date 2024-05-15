#pragma once

#include <string>
#include <utility>
#include <iostream>

#include "rwmode.hpp"
#include "format.hpp"

#include "type/uint.hpp"
#include "type/bool.hpp"

using namespace Utility;

namespace Parser {

    struct Option final {
        std::string name;
        std::string description;
        std::pair<uint64_t, uint64_t> bit_range;
        Format format;

        //TODO memory leak
        Type type() const {
            uint64_t size = bit_range.second - bit_range.first + 1; // [4; 8] = 5bits 
            if (size == 1) 
                return Bool();
            else if (size <= 8)
                return Uint8();
            else if (size <= 16)
                return Uint16();
            else if (size <= 32)
                return Uint32();
            else
                return Uint64();
        }

        void dump() const {
            std::cout << "Option:" << "\n"
                << "\t\t" << "name: " << name << "\n"
                << "\t\t" << "description: " << description << "\n"
                << "\t\t" << "bit_range: [" << bit_range.first << ", " << bit_range.second << "]" << "\n"
                << "\t\t" << "format: " << format << std::endl;
        }
    };

}; /* Parser */