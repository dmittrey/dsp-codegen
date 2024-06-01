#pragma once

#include "interface/iserializer.hpp"

namespace Generate {

    std::unique_ptr<ISerializer> make_file_serializer(const std::string& fname);

}; /* Generate */