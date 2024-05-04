#pragma once

#ifndef yyFlexLexer
#include <FlexLexer.h>
#endif

#include <iostream>
#include <vector>
#include <string>

#include "uint.hpp"
#include "format.hpp"

using namespace Utility;

class RegLexer : public yyFlexLexer {
    struct Register {
        std::string family_;
        std::string name_;
        uint64_t addr_;
        uint64_t offset_;
        uint64_t size_;
        Format fmt_;

        void print() const {
            std::cout << "Register:" << "\n"
                << "\tFamily: " << family_ << "\n"
                << "\tName: " << name_ << "\n"
                << "\tAddr: " << addr_ << "\n"
                << "\tOffset: " << offset_ << "\n"
                << "\tSize: " << size_ << "\n"
                << "\tFormat: " << fmt_ << "\n"
                << std::endl;
        }
        
        Type type() const {
            switch (size_)
            {
            case 8:
                return Uint8{};
            case 16:
                return Uint16{};
            case 32:
                return Uint32{};
            case 64:
                return Uint64{};
            default:
                exit(1);
            }
        }
    };

    std::vector<Register> vec = {};
    Register r;

    int process_family() {
        r.family_ = yytext;
#ifdef DEBUG_LEX
        std::cout << "FAMILY: <" << r.family_ << ">" << std::endl; 
#endif
        return 1;
    }

    int process_name() {
        r.name_ = yytext;
#ifdef DEBUG_LEX
        std::cout << "NAME: <" << r.name_ << ">" << std::endl; 
#endif
        return 1;
    }

    int process_address() {
        r.addr_ = std::stoi(yytext, nullptr, 16);
#ifdef DEBUG_LEX
        std::cout << "ADDRESS: <" << r.addr_ << ">" << std::endl;
#endif 
        return 1;
    }

    int process_offset() {
        r.offset_ = std::stoi(yytext);
#ifdef DEBUG_LEX
        std::cout << "OFFSET: <" << r.offset_ << ">" << std::endl;
#endif 
        return 1;
    }

    int process_size() {
        r.size_ = std::stoi(yytext);
#ifdef DEBUG_LEX
        std::cout << "SIZE: <" << r.size_ << ">" << std::endl;
#endif 
        return 1;
    }    

    int process_type(Format fmt) {
        r.fmt_ = fmt;
        vec.push_back(r);
#ifdef DEBUG_LEX
        std::cout << "TYPE: <" << r.fmt_ << ">" << std::endl;
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
    void print() const {
        for (auto reg : vec)
            reg.print();
    }
};