#pragma once

#include <string>

enum RegType {
    HEX_UNSIGNED = 0,
    HEX_SIGNED, 
    FP_UNSIGNED, /* u4q3 */
    FP_SIGNED, /* s4q3 */
    FP_SIGN_MAGNITUDE, /* sm4q3 */
    FP_TWOS_COMPLEMENT, /* t4q3 */
};

struct Register {
    std::string family;
    std::string name;
    uint64_t addr;
    uint64_t offset;
    RegType type;
};