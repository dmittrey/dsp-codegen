#pragma once

#include "iserializer.hpp"

namespace Serialize {

    std::unique_ptr<ISerializer> make_file_serializer(const std::string& fname);

}; /* Serialize */