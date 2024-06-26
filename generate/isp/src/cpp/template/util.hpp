#pragma once

#include "cpp/types.hpp"
#include "cpp/model/macro.hpp"

using namespace stx::cpp;

namespace gen {

    namespace cpp {

        namespace tmplt {

            const std::string ScaleMacroName = "SCALE_FACTOR";

            std::string opt_modifier_name(const util::Register& reg, const util::Option& opt) {
                return reg.name + '_' + 's' + '_' + opt.name;
            }

            std::string opt_selector_name(const util::Register& reg, const util::Option& opt) {
                return reg.name + '_' + 'g' + '_' + opt.name;
            }

            std::string set_ioctl_name(const util::Register& reg, const util::Option& opt) {
                return std::string("IOCTL") + '_' + reg.name + "_S_" + opt.name;
            }

            std::string get_ioctl_name(const util::Register& reg, const util::Option& opt) {
                return std::string("IOCTL") + '_' + reg.name + "_G_" + opt.name;
            }

            std::string to_fixed_name(const util::Register& reg, const util::Option& opt) {
                return reg.name + '_' + opt.name + "_to_fixed";
            }

            std::string to_float_name(const util::Register& reg, const util::Option& opt) {
                return reg.name + '_' + opt.name + "_to_float";
            }

            Type log_type(const util::Option& o) {
                auto bits_cnt = o.log_size();
                if (o.format() == util::HEX_UNSIGNED) {
                    if (bits_cnt == 1)
                        return t::Bool();
                    else if (bits_cnt <= 8)
                        return t::Uint8();
                    else if (bits_cnt <= 16)
                        return t::Uint16();
                    else if (bits_cnt <= 32)
                        return t::Uint32();
                    else
                        return t::Uint64();
                } else if (o.format() == util::HEX_SIGNED) {
                    if (bits_cnt == 1)
                        return t::Bool();
                    else if (bits_cnt <= 8)
                        return t::Int8();
                    else if (bits_cnt <= 16)
                        return t::Int16();
                    else if (bits_cnt <= 32)
                        return t::Int32();
                    else
                        return t::Int64();
                } else {
                    return t::Double();
                }
            }

            static Type hw_type(const util::Option& o) {
                auto size = o.hw_size();
                if (size == 1)
                    return t::Bool();
                else if (size <= 8)
                    return t::Uint8();
                else if (size <= 16)
                    return t::Uint16();
                else if (size <= 32)
                    return t::Uint32();
                else
                    return t::Uint64();
            }

        }; /* template */

    }; /* c++ */

}; /* generate */