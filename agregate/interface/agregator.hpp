#pragma once

#include "interface/iserializer.hpp"

using namespace Generate;

namespace Agregate {

    struct IAgregator {
        virtual void process(std::unique_ptr<ISerializer> &user, std::unique_ptr<ISerializer> &ioctl) const = 0;
        virtual ~IAgregator() { };
    };

}; /* Agregate */