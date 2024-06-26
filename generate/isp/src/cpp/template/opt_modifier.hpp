#pragma once

#include "util.hpp"

#include "cpp/model/function.hpp"
#include "cpp/model/rval.hpp"

using namespace stx::cpp;

namespace gen {

    namespace cpp {

        namespace tmplt {

            Function* OptModifier(const util::Register& reg, const util::Option& opt) {
                auto opt_param = RVal{log_type(opt), opt.name};
                auto fd_param = RVal{t::Cint(), "fd"};

                auto func = new Function{t::Cint(), opt_modifier_name(reg, opt)};

                func->params_set<RVal>({fd_param, opt_param});
                if (opt.is_float_point()) {
                    func->statement_add(hw_type(opt).code() + " val = " + to_fixed_name(reg, opt) + '(' + opt.name + ')');
                    func->statement_add("return ioctl(fd, " + set_ioctl_name(reg, opt) + ", " + "&val" + ")");
                } else {
                    func->statement_add("return ioctl(fd, " + set_ioctl_name(reg, opt) + ", " + '&' + opt_param.name + ")");
                }

                return func;
            };
            
        }; /* template */

    }; /* c++ */

}; /* generate */