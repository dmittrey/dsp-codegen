#pragma once

#include <vector>
#include <string>

#include "option.hpp"

namespace Parser {

    struct Register {
        std::string name;
        uint64_t address;
        std::string description;
        uint64_t size;
        RWMode mode;
        std::vector<Option> options;

        void dump() const {
            std::cout << "Register:" << "\n"
                << "\t" << "name: " << name << "\n"
                << "\t" << "address: " << address << "\n"
                << "\t" << "description: " << description << "\n"
                << "\t" << "size: " << size << "\n"
                << "\t" << "RWMode: " << mode << std::endl;

            for (const auto& op : options)
                op.dump();
        }
    };

}; /* Parser */