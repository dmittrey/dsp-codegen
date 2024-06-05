#pragma once

#include "cpp/model/function.hpp"

namespace stx {

    namespace cpp {

        struct IoctlFunction final : Function {
        private:
            const std::string ioctl_macro_;
            const std::optional<RVal> self_arg_;

        public:
            IoctlFunction(const Type &type, const std::string &name, const std::string& ioctl_macro, 
                            const std::optional<RVal>& self_arg = std::nullopt) : 
                                Function(type, name), ioctl_macro_(ioctl_macro), self_arg_(self_arg) {
                headers_.push_back("sys/ioctl.h");
                param_add<RVal>({t::make_cint(), "fd"});
                if (self_arg.has_value())
                    param_add<RVal>(*self_arg);
            }

        public:
            const std::string payload() const override {
                return std::string("ioctl") + '(' 
                        + "fd" + ',' + ' ' 
                        + ioctl_macro_ 
                        + (self_arg_.has_value() ? std::string(",") + " " + self_arg_->name : "")
                        + ')' + ';' + '\n';
            }
        };

    }; /* cpp */

}; /* syntax */