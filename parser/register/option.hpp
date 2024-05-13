#pragma once

#include <string>
#include <utility>

#include "rwmode.hpp"

namespace Parser {

    struct Option {
        std::string reg_name; // Need remove
        std::string name;
        std::string desc;
        std::pair<uint64_t, uint64_t> bit_range;
        RWMode rw_mode;
    };

}; /* Parser */