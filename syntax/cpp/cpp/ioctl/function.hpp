#pragma once

#include "cpp/model/function.hpp"

namespace Syntax {

    struct IoctlCppFunction final : CppFunction {
    private:
        const std::string ioctl_macro_;
        const std::optional<CppRVal> self_arg_;

    public:
        IoctlCppFunction(const Type &type, const std::string &name, const std::string& ioctl_macro) : 
                            CppFunction(type, name), ioctl_macro_(ioctl_macro), self_arg_(std::nullopt) {
            headers_.push_back("sys/ioctl.h");                        
        }

        IoctlCppFunction(const Type &type, const std::string &name, const std::string& ioctl_macro, const CppRVal& self_arg) : 
                            CppFunction(type, name), ioctl_macro_(ioctl_macro), self_arg_(self_arg) {
            headers_.push_back("sys/ioctl.h");
            param_add(std::make_unique<CppRVal>(self_arg));
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

}; /* Syntax */