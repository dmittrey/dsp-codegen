#pragma once

#include <string>
#include <cstdint>

#include "format.hpp"

namespace util {

    struct FixedP final {
        Format format;
        uint8_t int_bits;
        uint8_t fract_bits;

        std::string str() const {
            switch (format) {
                case HEX_UNSIGNED:
                    return "u" + std::to_string(int_bits);
                case HEX_SIGNED:
                    return "s" + std::to_string(int_bits);
                case FP_UNSIGNED: /* u4q3 */
                    return "u" + std::to_string(int_bits) + "q" + std::to_string(fract_bits);
                case FP_SIGNED: /* s4q3 */
                    return "s" + std::to_string(int_bits) + "q" + std::to_string(fract_bits);
                case FP_SIGN_MAGNITUDE: /* sm4q3 */
                    return "sm" + std::to_string(int_bits) + "q" + std::to_string(fract_bits);
                case FP_TWOS_COMPLEMENT: /* t4q3 */
                    return "t" + std::to_string(int_bits) + "q" + std::to_string(fract_bits);
            }   
        }
    };

}; /* utility */