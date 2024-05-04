/*
    Abstraction to fill files with generated code
*/
#pragma once

#include <iostream>
#include <vector>

#include "translation.hpp"

namespace Generate {

    void render_file(std::ostream &out, std::vector<Function> &unit) {
        std::vector <std::string> headers;
        std::vector <std::string> functions;   
    };

    void render(std::ostream& out, Function &unit) {
        out << unit.ret_type.name() << "\t" 
            << unit.name << "(";
        
        int i = 0;
        for (auto arg : unit.arg_list)
            out << arg.first.name() << " " << arg.second;
            if (i++ != unit.arg_list.size() - 1)
                out << ", ";
        
        out << ")" << " " 
            << "{" << "\n"
            << unit.op.payload() << "\n"
            << "}" 
            << std::endl;
    };

}; /* Generate */