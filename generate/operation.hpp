/*
    All abstractions to describe function
    - Types
*/
#pragma once

#include <string>

namespace Generate {

    struct Operation {
        virtual std::string payload() { return ""; };
        virtual ~Operation() {}
    };

    struct Getter final : public Operation {
        std::string payload() override {
            return "ioctl(...)";
        }
    };

    struct Setter final : public Operation {
        std::string payload() override {
            return "ioctl(...)";
        }
    };

}; /* Generate */