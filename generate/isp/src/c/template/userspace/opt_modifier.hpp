#pragma once

#include "util.hpp"
#include "lexem.hpp"

#include "c/model/function.hpp"
#include "c/model/rval.hpp"

using namespace stx::c;

namespace gen {

    namespace c {

        namespace tmplt {

            Function* OptModifier(const util::Register& reg, const util::Option& opt) {
                auto opt_param = RVal{log_type(opt), opt.name};
                auto fd_param = RVal{t::Cint(), "fd"};

                auto func = new Function{t::Cint(), opt_modifier_name(reg, opt)};

                func->params_set<RVal>({fd_param, opt_param});
                if (opt.is_float_point()) {
                    func->statement_add(Lexem().Concat(s_hw_type(opt)).Concat("val").Equal()
                                        .Concat(to_fixed_name(reg, opt)).Args({opt.name}));
                    func->statement_add(Lexem().Return()
                                        .Ioctl().Args({fd_param.name, set_ioctl_name(reg, opt), "&val"}));
                } else {
                    func->statement_add(Lexem().Return()
                                        .Ioctl().Args({fd_param.name, set_ioctl_name(reg, opt), '&' + opt_param.name}));
                }

                return func;
            };
            
        }; /* template */

    }; /* c */

}; /* generate */