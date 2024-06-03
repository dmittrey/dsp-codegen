#include "isp/codegen.hpp"

#include "register/register.hpp"

#include "cpp/layout.hpp"
#include "cpp/extra.hpp"

#include "cpp/model/comment.hpp"
#include "cpp/model/function.hpp"
#include "cpp/model/rval.hpp"
#include "cpp/model/structure.hpp"

#include "cpp/ioctl/function.hpp"

using Utility::Register;
using Utility::Option;

using serialize::ISerializer;

using namespace stx;

namespace Generate {

    Type option_type(const Option &opt)
    {
        auto opt_size = opt.size();
        if (opt_size == 1)
            return cpp::t::make_bool();
        else if (opt_size <= 8)
            return cpp::t::make_uint8();
        else if (opt_size <= 16)
            return cpp::t::make_uint16();
        else if (opt_size <= 32)
            return cpp::t::make_uint32();
        else
            return cpp::t::make_uint64();
    }

    void generate_userspace_ctrls(const std::vector<Register>& regs, std::unique_ptr<ISerializer>& out) {
        cpp::Layout layout;

        for (const auto& reg : regs) {
            layout.add_model(new cpp::Comment(reg.description));
            auto s = new cpp::Structure{cpp::t::make_struct(), reg.name};
            layout.add_model(s);

            for (const auto& opt : reg.options) {
                auto opt_type = option_type(opt);

                s->field_add<cpp::Comment>(opt.description); // :((((((
                s->field_add({opt_type, opt.name, opt.size()});

                // Option modifier
                // Later... Need to move to Base, delete all methods and use derived CppBool
                auto opt_param = cpp::RVal{opt_type, opt.name};
                auto sf = new cpp::IoctlFunction{cpp::t::make_void(), reg.name + '_' + "s" + '_' + opt.name, 
                                                std::string("IOCTL_") + "S_" + opt.name, opt_param};
                layout.add_model(sf);

                // Option getter
                auto gf = new cpp::IoctlFunction{opt_type, reg.name + '_' + "g" + '_' + opt.name,
                                                std::string("IOCTL_") + "G_" + opt.name};
                layout.add_model(gf);
            }

            auto extra = 32 - s->size();
            s->field_add({cpp::t::make_uint32(), "align", extra});
        }

        out->serialize(layout);
    }

    void generate_ioctl_enum(const std::vector<Utility::Register>& regs, std::unique_ptr<ISerializer>& out) {
        cpp::Layout layout;

        auto e = cpp::make_anon_enum();
        layout.add_model(e);

        for (const auto& reg : regs) {
            for (const auto& opt : reg.options) {
                // Option modifier
                e->field_add({cpp::t::make_empty(), std::string("IOCTL") + '_' + reg.name + "_S_" + opt.name});

                // Option getter
                e->field_add({cpp::t::make_empty(), std::string("IOCTL") + '_' + reg.name + "_G_" + opt.name});
            }
        }

        out->serialize(layout);
    }

}; /* Generate */