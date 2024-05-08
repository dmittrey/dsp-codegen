#pragma once

#include "type.hpp"

namespace Utility {

    struct Uint : public Type {
        std::string header() const override {
            return {"cstdint"};
        }
    };

    struct Uint8 final : public Uint {
        std::string name() const override {
            return "uint8_t";
        }
    };

    struct Uint16 final : public Uint {
        std::string name() const override {
            return "uint16_t";
        }
    };

    struct Uint32 final : public Uint {
        std::string name() const override {
            return "uint32_t";
        }
    };

    struct Uint64 final : public Uint {
        std::string name() const override {
            return "uint64_t";
        }
    };

    struct String final : public Type {
        std::string header() const override {
            return {"string"};
        }

        std::string name() const override {
            return "std::string";
        }
    };

}; /* Utility */