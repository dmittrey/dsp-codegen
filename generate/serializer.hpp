#pragma once

#include <memory>
#include <iostream>
#include <fstream>

#include "iserializer.hpp"

namespace Generate {

    struct Serializer : ISerializer {
    protected:
        std::unique_ptr<std::ostream> out;
    };

    struct FileSerializer final : Serializer {
        FileSerializer(const std::string &file_name) { out = std::make_unique<std::ofstream>(file_name); };
        FileSerializer(const std::string &&file_name) { out = std::make_unique<std::ofstream>(file_name); };

        void serialize(const ILayout& layout) override {
            *out << layout.render() << std::endl;
        };
    };

}; /* Generate */