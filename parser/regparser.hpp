#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

#include <json/json.h>

#include "register/register.hpp"

namespace Parser {

    class RegParser final {
    private:
        const std::unique_ptr<std::ifstream> ifstreamp;
        std::vector<Register> vec = {};
    
    public:
        RegParser(const std::string &fname) : ifstreamp(std::make_unique<std::ifstream>(fname)) {
			Json::Value root;
			*ifstreamp >> root;
			std::cout << root["options"].size();
		}
    
    public:
        const std::vector<Register>& registers() const { return vec; }
        void print() const {
            for (const auto& reg : vec)
                reg.dump();
        }
    };

}; /* Parser */