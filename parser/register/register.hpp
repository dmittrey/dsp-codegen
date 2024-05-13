#pragma once

#include <vector>
#include <string>

#include "option.hpp"

namespace Parser {

    struct Register {
        std::string name;
        uint64_t offset;
        uint64_t size;
        std::vector<Option> options;

        void dump() const {
            std::cout << "Register:" << "\n"
                << "\t" << "name: " << name << "\n"
                << "\t" << "offset: " << offset << "\n"
                << "\t" << "size: " << size << std::endl;

            for (const auto& op : options)
                op.dump();
        }
    };

}; /* Parser */