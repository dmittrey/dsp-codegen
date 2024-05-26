#pragma once

#include "register.hpp"

#include "interface/iserializer.hpp"

namespace Generate {

    void process_userspace(const std::vector<Utility::Register>& regs, std::unique_ptr<ISerializer>& out);
    void process_ioctl_enum(const std::vector<Utility::Register>& regs, std::unique_ptr<ISerializer>& out);

}; /* Generate */