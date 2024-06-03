#pragma once

#include "iserializer.hpp"

namespace serialize {

    std::unique_ptr<ISerializer> make_file_serializer(const std::string& fname);

}; /* serialize */