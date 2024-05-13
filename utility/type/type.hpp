/*
    Share same types with parse and generate modules to compatible interface
*/
#pragma once

#include <string>
#include <vector>
#include <optional>

/* TODO Types oriented on c++ specific, need to fix later */

namespace Utility {

    struct Type {
    public:
        std::string name;
        std::optional<std::string> header;

    public:
        Type(const std::string& name_, const std::string& header_) :  name(name_), header(header_) {}
        Type(const std::string& name_) :  name(name_), header(std::optional<std::string>()) {}
        Type(const Type& obj) : header(obj.header), name(obj.name) {}

    public:
        virtual ~Type() {}
    };

}; /* Utility */