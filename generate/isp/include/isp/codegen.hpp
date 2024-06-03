#pragma once

#include "iserializer.hpp"
#include "register/register.hpp"

namespace Generate {

    void generate_userspace_ctrls(const std::vector<util::Register>& regs, std::unique_ptr<serialize::ISerializer>& out);
    void generate_ioctl_enum(const std::vector<util::Register>& regs, std::unique_ptr<serialize::ISerializer>& out);

}; /* Generate */