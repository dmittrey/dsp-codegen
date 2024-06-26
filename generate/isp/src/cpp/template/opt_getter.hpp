#pragma once

#include "util.hpp"

#include "cpp/model/function.hpp"
#include "cpp/model/ptr.hpp"

using namespace stx::cpp;

namespace gen {

    namespace cpp {

        namespace tmplt {

            Function* OptGetter(const util::Register& reg, const util::Option& opt) {
                auto opt_param = Ptr{log_type(opt), opt.name};
                auto fd_param = RVal{t::Cint(), "fd"};

                auto func = new Function{t::Cint(), opt_selector_name(reg, opt)};

                func->params_set<RVal>({fd_param, opt_param});
                if (opt.is_float_point()) {
                    func->statement_add(hw_type(opt).code() + " val");
                    func->statement_add(t::Cint().code() + " ret = ioctl(fd, " + get_ioctl_name(reg, opt) + ", " + "&val" + ")");
                    func->statement_add("*" + opt_param.name + " = " + to_float_name(reg, opt) + '(' + "val" +')');
                    func->statement_add("return ret");
                } else {
                    func->statement_add("return ioctl(fd, " + get_ioctl_name(reg, opt) + ", " + opt_param.name + ")");
                }

                return func;
            };
            
        }; /* template */

    }; /* c++ */

}; /* generate */