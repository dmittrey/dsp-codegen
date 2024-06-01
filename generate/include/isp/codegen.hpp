#pragma once

#include "register/register.hpp"

#include "interface/iserializer.hpp"

namespace Generate {

    void generate_userspace_ctrls(const std::vector<Utility::Register>& regs, std::unique_ptr<ISerializer>& out);
    void generate_ioctl_enum(const std::vector<Utility::Register>& regs, std::unique_ptr<ISerializer>& out);

}; /* Generate */