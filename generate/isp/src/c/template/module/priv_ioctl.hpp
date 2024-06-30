#pragma once

#include "lexem.hpp"

#include "c/model/function.hpp"

using namespace stx::c;

namespace gen {

    namespace c {

        namespace tmplt {

            Function* PrivateIoctlFunction(const std::string& name, const std::vector<util::Register>& regs) {
                auto dev_param = RVal{Type("struct device*"), "dev"};
                auto cmd_param = RVal{Type("unsigned int"), "cmd"};
                auto arg_param = RVal{Type("void __user*"), "args"};

                auto ret_var = RVal{t::Cint(), "ret"};
                auto val_var = RVal{Type("u32"), "val"};

                auto func = new Function{t::Clong(), name};
                func->params_set<RVal>({dev_param, cmd_param, arg_param});

                func->statement_add(Lexem().Concat(ret_var).Equal().Concat("0"));
                func->statement_add(Lexem().Concat(val_var).Equal().Star().Concat(arg_param.name));

                auto IoctlSwitch = Lexem().Concat("switch").Args({cmd_param.name}).Concat(" {\n");

                for (const auto& reg : regs) {
                    for (const auto& opt : reg.options) {
                        if (reg.mode != util::RWMode::RO && !opt.s_ioctl.has_value())
                            IoctlSwitch.Concat(tmplt::OptSetIoctlCase(tmplt::set_ioctl_name(reg, opt), 
                                            reg.address + opt.bit_range.first, "val"));
                    
                        if (reg.mode != util::RWMode::WO && !opt.g_ioctl.has_value())
                            IoctlSwitch.Concat(tmplt::OptGetIoctlCase(tmplt::set_ioctl_name(reg, opt), 
                                            reg.address + opt.bit_range.first, "val"));
                    }
                }

                IoctlSwitch.Concat("default: \n").Concat("\tbreak; \n").Concat("}");

                func->statement_add(IoctlSwitch);

                func->statement_add(Lexem().Return().Concat(ret_var.name));

                return func;
            };
            
        }; /* template */

    }; /* c */

}; /* generate */