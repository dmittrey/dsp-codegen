#pragma once

#include "type.hpp"

namespace Utility {

    struct Uint : public Type {
        std::vector<std::string> headers() override {
            return {"cstdint"};
        }
    };

    struct Uint8 final : public Uint {
        std::string name() override {
            return "uint8_t";
        }
    };

    struct Uint16 final : public Uint {
        std::string name() override {
            return "uint16_t";
        }
    };

    struct Uint32 final : public Uint {
        std::string name() override {
            return "uint32_t";
        }
    };

    struct Uint64 final : public Uint {
        std::string name() override {
            return "uint64_t";
        }
    };

}; /* Utility */