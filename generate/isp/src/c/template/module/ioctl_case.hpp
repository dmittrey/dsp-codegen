#pragma once

#include "c/model/case.hpp"
#include "c/model/comment.hpp"

#include "lexem.hpp"

using namespace stx::c;

namespace gen {

    namespace c {

        namespace tmplt {

            Case OptSetIoctlCase(const std::string& ioctl_name, uint32_t reg_addr, const std::string& val_name) {
                auto s = Case{ioctl_name};
                s.field_add<std::string>(
                    Lexem().Concat("__raw_writel").Args({'*' + val_name, std::to_string(reg_addr)})
                );
                s.field_add<std::string>(
                    Lexem().Break()
                );
                return s;
            };

            Case OptGetIoctlCase(const std::string& ioctl_name, uint32_t reg_addr, const std::string& val_name) {
                auto s = Case{ioctl_name};
                s.field_add<std::string>(
                    Lexem().Star().Concat(val_name).Equal().Concat("__raw_readl").Args({std::to_string(reg_addr)})
                );
                s.field_add<std::string>(
                    Lexem().Break()
                );
                return s;
            };
            
        }; /* template */

    }; /* c */

}; /* generate */