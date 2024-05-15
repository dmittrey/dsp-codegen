#pragma once

#include <string>
#include <utility>
#include <iostream>

#include "rwmode.hpp"
#include "format.hpp"

#include "cpp/type/uint.hpp"
#include "cpp/type/bool.hpp"

using namespace Utility;
using namespace Generate;

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
                return Types::make_bool();
            else if (size <= 8)
                return Types::make_uint8();
            else if (size <= 16)
                return Types::make_uint16();
            else if (size <= 32)
                return Types::make_uint32();
            else
                return Types::make_uint64();
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