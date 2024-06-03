#pragma once

#include "cpp/model/function.hpp"

namespace stx {

    namespace cpp {

        struct IoctlFunction final : Function {
        private:
            const std::string ioctl_macro_;
            const std::optional<RVal> self_arg_;

        public:
            IoctlFunction(const Type &type, const std::string &name, const std::string& ioctl_macro) : 
                                Function(type, name), ioctl_macro_(ioctl_macro), self_arg_(std::nullopt) {
                headers_.push_back("sys/ioctl.h");
                param_add<RVal>({t::make_int(), "fd"});
            }

            IoctlFunction(const Type &type, const std::string &name, const std::string& ioctl_macro, const RVal& self_arg) : 
                                Function(type, name), ioctl_macro_(ioctl_macro), self_arg_(self_arg) {
                headers_.push_back("sys/ioctl.h");
                param_add<RVal>({t::make_int(), "fd"});
                param_add<RVal>(self_arg);
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