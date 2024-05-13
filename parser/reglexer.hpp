#pragma once

#ifndef yyFlexLexer
#include <FlexLexer.h>
#endif

#include <iostream>
#include <vector>
#include <string>

#include "register/option.hpp"

#include "eformat.hpp"

using namespace Parser;
using namespace Common;

class RegLexer : public yyFlexLexer {
private:
    std::vector<Option> vec = {};
    Option r;

private:
    /* Reg name */
    int process_regname() {
        r.reg_name = yytext;
#ifdef DEBUG_LEX
        std::cout << "REG NAME: <" << yytext << ">" << std::endl; 
#endif
        return 1;
    }

    int process_name() {
        r.name = yytext;
#ifdef DEBUG_LEX
        std::cout << "NAME: <" << yytext << ">" << std::endl; 
#endif
        return 1;
    }

    int process_desc() {
        r.desc = yytext;
#ifdef DEBUG_LEX
        std::cout << "DESCRIPTION: <" << yytext << ">" << std::endl;
#endif 
        return 1;
    }

    int process_range() {
        // r.bit_range
        // Type *type = new Uint64();
        // r.fields.emplace_back(type, "offset");
#ifdef DEBUG_LEX
        std::cout << "RANGE: <" << yytext << ">" << std::endl;
#endif 
        return 1;
    }

    int process_rwmode() {
        // Type *type = new Uint64();
        // r.fields.emplace_back(type, "size");
#ifdef DEBUG_LEX
        std::cout << "RWMODE: <" << yytext << ">" << std::endl;
#endif 
        return 1;
    }    

    int process_type(FormatEnum fmt) {
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

public:
    std::vector<Option> registers() const { return vec; }
};