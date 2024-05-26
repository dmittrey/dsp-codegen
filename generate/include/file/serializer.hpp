#pragma once

#include "syntax/generic/serializer.hpp"

namespace Generate {

    struct FileSerializer final : Serializer {
        FileSerializer(const std::string &fname) : Serializer(std::make_unique<std::ofstream>(fname)) {};
    };

}; /* Generate */