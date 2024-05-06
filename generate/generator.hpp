#pragma once

#include <memory>

namespace Generate {

    /* RAII for render layouts */
    struct Render {
        
        virtual ~Render() {};
    };

    class FileRender : public Render {

    };

}; /* Generate */