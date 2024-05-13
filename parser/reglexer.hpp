#pragma once

#ifndef yyFlexLexer
#include <FlexLexer.h>
#endif

#include <iostream>
#include <vector>
#include <string>

#include "register/register.hpp"

using namespace Parser;

class RegLexer : public yyFlexLexer {
private:
    std::vector<Register> vec = {};
    Register r;
    Option o;

private:
    int process_reg_name() {
        r.name = yytext;
        r.name.pop_back();
#ifdef DEBUG_LEX
        std::cout << "REG NAME: <" << yytext << ">" << std::endl; 
#endif
        return 1;
    }

    int process_reg_offset() {
        r.offset = std::stoi(yytext, nullptr, 16);
#ifdef DEBUG_LEX
        std::cout << "REG OFFSET: <" << yytext << ">" << std::endl; 
#endif
        return 1;
    }

    int process_reg_size() {
        r.size = std::stoi(yytext);
#ifdef DEBUG_LEX
        std::cout << "REG SIZE: <" << yytext << ">" << std::endl; 
#endif
        return 1;
    }

    int process_reg_name_retry() {
        vec.push_back(r);
        r.name = yytext;
        r.name.pop_back();
#ifdef DEBUG_LEX
        std::cout << "REG NAME: <" << yytext << ">" << std::endl; 
#endif
        return 1;
    }

    int process_opt_name() {
        o.name = yytext;
        o.name.pop_back();
#ifdef DEBUG_LEX
        std::cout << "OPT NAME: <" << yytext << ">" << std::endl; 
#endif
        return 1;
    }

    int process_opt_desc() {
        o.desc = yytext;
        o.desc.pop_back();
#ifdef DEBUG_LEX
        std::cout << "OPT DESCRIPTION: <" << yytext << ">" << std::endl;
#endif 
        return 1;
    }

    int process_opt_range() {
        o.bit_range.first = yytext[1] - '0';
        o.bit_range.second = yytext[4] - '0'; // TODO Need to test with 2 or more character values
#ifdef DEBUG_LEX
        std::cout << "OPT RANGE: <" << yytext << ">" << std::endl;
#endif 
        return 1;
    }

    int process_opt_rwmode(RWMode mode) {
        o.rw_mode = mode;
#ifdef DEBUG_LEX
        std::cout << "OPT RWMODE: <" << yytext << ">" << std::endl;
#endif 
        return 1;
    }    

    int process_opt_type(Format fmt) {
        o.format = fmt;
        r.options.push_back(o);
#ifdef DEBUG_LEX
        std::cout << "TYPE: <" << yytext << ">" << std::endl;
#endif 
        return 1;
    }

// TODO Обработка ошибок пропуск регистра
    int process_unknown() {
        std::cout << " UNKNOWN <" << yytext << ">" << std::endl; 
        return 1;
    }

public:
    int yylex() override;
    int yywrap() override {
        vec.push_back(r);
        return 1;
    }

public:
    std::vector<Register> registers() const { return vec; }
    void print() const {
        for (const auto& reg : vec)
            reg.dump();
    }
};