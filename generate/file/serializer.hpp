#pragma once

#include "generic/serializer.hpp"

namespace Generate {

    struct FileSerializer final : Serializer {
        FileSerializer(const std::string &file_name) : Serializer(std::make_unique<std::ofstream>(file_name)) {};
    };

}; /* Generate */