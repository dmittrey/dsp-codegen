#pragma once

#include "iserializer.hpp"

#include "register/register.hpp"

namespace gen {

    void generate_userspace_ctrls(const std::vector<util::Register>& regs, std::unique_ptr<serialize::ISerializer>& out, const std::string& ioctl_enm_path);
    void generate_ioctl_enum(const std::vector<util::Register>& regs, std::unique_ptr<serialize::ISerializer>& out);

}; /* generate */