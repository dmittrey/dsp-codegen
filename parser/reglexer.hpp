#pragma once

#ifndef yyFlexLexer
#include <FlexLexer.h>
#endif

#include <iostream>
#include <vector>
#include <string>

#include "register.hpp"

#include "type/uint.hpp"
#include "type/string.hpp"
#include "type/format.hpp"

#include "eformat.hpp"

using namespace Utility;
using namespace Common;

class RegLexer : public yyFlexLexer {
private:
    std::vector<Register> vec = {};
    Register r;

private:
    int process_family() {
        Type *type = new String();
        r.fields.emplace_back(type, "family");
#ifdef DEBUG_LEX
        // std::cout << "FAMILY: <" << yytext << ">" << std::endl; 
#endif
        return 1;
    }

    int process_name() {
        r.name = yytext;
#ifdef DEBUG_LEX
        // std::cout << "NAME: <" << yytext << ">" << std::endl; 
#endif
        return 1;
    }

    int process_address() {
        Type *type = new Uint64();
        r.fields.emplace_back(type, "address");
#ifdef DEBUG_LEX
        // std::cout << "ADDRESS: <" << yytext << ">" << std::endl;
#endif 
        return 1;
    }

    int process_offset() {
        Type *type = new Uint64();
        r.fields.emplace_back(type, "offset");
#ifdef DEBUG_LEX
        // std::cout << "OFFSET: <" << yytext << ">" << std::endl;
#endif 
        return 1;
    }

    int process_size() {
        Type *type = new Uint64();
        r.fields.emplace_back(type, "size");
#ifdef DEBUG_LEX
        // std::cout << "SIZE: <" << yytext << ">" << std::endl;
#endif 
        return 1;
    }    

    int process_type(FormatEnum fmt) {
        Type *type = new Format();
        r.fields.emplace_back(type, "format");

        vec.push_back(r);
        r.fields.clear();
#ifdef DEBUG_LEX
        // std::cout << "TYPE: <" << yytext << ">" << std::endl;
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
    std::vector<Register> registers() const { return vec; }
};