#pragma once

namespace Agregate {

    struct IAgregator {
        virtual void process() const = 0;
        virtual ~IAgregator() { };
    };

}; /* Agregate */