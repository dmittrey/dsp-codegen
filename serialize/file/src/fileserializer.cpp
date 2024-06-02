#include "serializer.hpp"

namespace Serialize {

    std::unique_ptr<ISerializer> make_file_serializer(const std::string& fname) {
        return std::make_unique<Serializer>(std::make_unique<std::ofstream>(fname));
    }

}; /* Serialize */