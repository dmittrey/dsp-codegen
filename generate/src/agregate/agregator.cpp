#include "agregate/interface.hpp"

#include "syntax/cpp/layout.hpp"
#include "syntax/cpp/extra.hpp"

#include "syntax/cpp/model/comment.hpp"
#include "syntax/cpp/model/function.hpp"
#include "syntax/cpp/model/rval.hpp"
#include "syntax/cpp/model/structure.hpp"

#include "syntax/cpp/ioctl/function.hpp"

using Utility::Register;
using Utility::Option;

namespace Generate {

    Type option_type(const Option &opt)
    {
        auto opt_size = opt.size();
        if (opt_size == 1)
            return Types::make_bool();
        else if (opt_size <= 8)
            return Types::make_uint8();
        else if (opt_size <= 16)
            return Types::make_uint16();
        else if (opt_size <= 32)
            return Types::make_uint32();
        else
            return Types::make_uint64();
    }

    void process_userspace(const std::vector<Register>& regs, std::unique_ptr<ISerializer>& out) {
        CppLayout layout;
        CppLayout ioctl_layout;

        auto e = make_anon_enum();
        ioctl_layout.add_model(e);

        for (const auto& reg : regs) {
            layout.add_model(new CppComment(reg.description));
            auto s = new CppStructure{Types::make_struct(), reg.name};
            layout.add_model(s);

            for (const auto& opt : reg.options) {
                auto opt_type = option_type(opt);

                s->field_add<CppComment>(opt.description); // :((((((
                s->field_add({opt_type, opt.name, opt.size()});

                // Option modifier
                // Later... Need to move to Base, delete all methods and use derived CppBool
                auto opt_param = CppRVal{opt_type, opt.name};
                auto sf = new IoctlCppFunction{Types::make_void(), reg.name + '_' + "s" + '_' + opt.name, 
                                                std::string("IOCTL_") + "S_" + opt.name, opt_param};
                e->field_add({Types::make_empty(), std::string("IOCTL_") + "S_" + reg.name + '_' + opt.name});
                layout.add_model(sf);

                // Option getter
                auto gf = new IoctlCppFunction{opt_type, reg.name + '_' + "g" + '_' + opt.name,
                                                std::string("IOCTL_") + "G_" + opt.name};
                e->field_add({Types::make_empty(), std::string("IOCTL_") + "G_" + opt.name});
                layout.add_model(gf);
            }

            auto extra = 32 - s->size();
            s->field_add({Types::make_uint32(), "align", extra});
        }

        out->serialize(layout);
    }

    void process_ioctl_enum(const std::vector<Utility::Register>& regs, std::unique_ptr<ISerializer>& out) {
        CppLayout layout;

        auto e = make_anon_enum();
        layout.add_model(e);

        for (const auto& reg : regs) {
            for (const auto& opt : reg.options) {
                // Option modifier
                e->field_add({Types::make_empty(), std::string("IOCTL_") + "S_" + reg.name + '_' + opt.name});

                // Option getter
                e->field_add({Types::make_empty(), std::string("IOCTL_") + "G_" + reg.name + '_' + opt.name});
            }
        }

        out->serialize(layout);
    }

}; /* Generate */