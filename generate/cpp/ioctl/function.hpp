#pragma once

#include "cpp/model.hpp"

namespace Generate {

    struct IoctlCppFunction final : CppFunction {
    private:
        const std::string ioctl_macro_;
        const std::optional<CppRVal> self_arg_;

    public:
        IoctlCppFunction(const CppRVal& name, const std::string& ioctl_macro) : 
                            CppFunction(name), ioctl_macro_(ioctl_macro), self_arg_(std::nullopt) {}

        IoctlCppFunction(const CppRVal& name, const std::string& ioctl_macro, const CppRVal& self_arg) : 
                            CppFunction(name), ioctl_macro_(ioctl_macro), self_arg_(self_arg) {
            param_add(self_arg);
        }

    public:
        const std::string payload() const override {
            return std::string("ioctl") + '(' 
                    + "fd" + ',' + ' ' 
                    + ioctl_macro_ + ',' + ' ' 
                    + (self_arg_.has_value() ? self_arg_->name.value_or("") : "")
                    + ')' + ';' + '\n';
        }
    };

}; /* Generate */