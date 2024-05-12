#pragma once

#include "type.hpp"

namespace Utility {

    struct Uint : Type {
        Uint(const std::string name) : Type(name, "cstdint") { }
    };

    struct Uint8 final : Uint {
        Uint8() : Uint("uint8_t") {}
    };

    struct Uint16 final : public Uint {
        Uint16() : Uint("uint16_t") {}
    };

    struct Uint32 final : public Uint {
        Uint32() : Uint("uint32_t") {}
    };

    struct Uint64 final : public Uint {
        Uint64() : Uint("uint64_t") {}
    };

    struct String final : Type {
        String() : Type("std::string", "string") { }
    };

}; /* Utility */