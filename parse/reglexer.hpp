#pragma once

#ifndef yyFlexLexer
#include <FlexLexer.h>
#endif

#include <iostream>
#include <vector>
#include <string>

#include "regtype.hpp"

class RegLexer : public yyFlexLexer {
    struct Register {
        std::string family;
        std::string name;
        uint64_t addr;
        uint64_t offset;
        RegType type;

        void print() const {
            std::cout << "Register:" << "\n"
                << "\tFamily: " << family << "\n"
                << "\tName: " << name << "\n"
                << "\tAddr: " << addr << "\n"
                << "\tOffset: " << offset << "\n"
                << "\tType: " << type << "\n"
                << std::endl;
        }
    };

    std::vector<Register> vec = {};
    Register r;

    int process_family() {
        r.family = yytext;
        return 1;
    }

    int process_name() {
        r.name = yytext;
        return 1;
    }

    int process_address() {
        r.addr = std::stoi(yytext, nullptr, 16);
        return 1;
    }

    int process_offset() {
        r.offset = std::stoi(yytext);
        return 1;
    }

    int process_type(RegType type) {
        r.type = type;
        vec.push_back(r);
        return 1;
    }

    int process_unknown() {
        std::cout << " UNKNOWN <" << yytext << ">" << std::endl; 
        return 1;
    }

public:
    int yylex() override;
    void print() const {
        for (auto reg : vec)
            reg.print();
    }
};