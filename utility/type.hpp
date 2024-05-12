/*
    Share same types with parse and generate modules to compatible interface
*/
#pragma once

#include <string>
#include <vector>

namespace Utility {

    struct Type {
    public:
        std::string name;
        std::string header;

    public:
        Type(const std::string name_, const std::string& header_) :  name(name_), header(header_) {}
        Type(const Type& obj) : header(obj.header), name(obj.name) {}

    public:
        virtual ~Type() {}
    };

}; /* Utility */