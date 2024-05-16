#pragma once

#include <string>
#include <optional>

namespace Utility {

    struct Type final {
    public:
        std::string name;
        std::optional<std::string> header;

    public:
        Type(const std::string& name_, const std::string& header_) :  name(name_), header(header_) {}
        Type(const std::string& name_) :  name(name_), header(std::optional<std::string>()) {}
        Type(const Type& obj) : header(obj.header), name(obj.name) {}
    };

}; /* Utility */