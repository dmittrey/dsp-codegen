#pragma once

#include "iserializer.hpp"

#include "register/register.hpp"

namespace gen {

    namespace cpp {

        std::unique_ptr<stx::ILayout> generate_userspace_ctrls(const std::vector<util::Register>& regs, const std::string& ioctl_enm_path);
        std::unique_ptr<stx::ILayout> generate_ioctl_enum(const std::vector<util::Register>& regs);

    }; /* C++ */

}; /* generate */