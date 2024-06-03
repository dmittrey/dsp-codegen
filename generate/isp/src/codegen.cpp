#include "isp/codegen.hpp"

#include "cpp/layout.hpp"
#include "cpp/extra.hpp"

#include "cpp/model/comment.hpp"
#include "cpp/model/function.hpp"
#include "cpp/model/rval.hpp"
#include "cpp/model/structure.hpp"

#include "cpp/ioctl/function.hpp"

using util::Register;
using util::Option;

using serialize::ISerializer;

using stx::gen::Type;

using namespace stx::cpp;

namespace gen {

    static Type option_type(const Option &opt)
    {
        auto opt_size = opt.size();
        if (opt_size == 1)
            return t::make_bool();
        else if (opt_size <= 8)
            return t::make_uint8();
        else if (opt_size <= 16)
            return t::make_uint16();
        else if (opt_size <= 32)
            return t::make_uint32();
        else
            return t::make_uint64();
    }

    static std::string set_ioctl_name(Register reg, Option opt) {
        return std::string("IOCTL") + '_' + reg.name + "_S_" + opt.name;
    }

    static std::string get_ioctl_name(Register reg, Option opt) {
        return std::string("IOCTL") + '_' + reg.name + "_G_" + opt.name;
    }

    void generate_userspace_ctrls(const std::vector<Register>& regs, std::unique_ptr<ISerializer>& out, const std::string& ioctl_enm_path) {
        Layout layout;
        layout.add_header(ioctl_enm_path);

        for (const auto& reg : regs) {
            layout.add_model(new Comment(reg.description));
            auto s = new Structure{t::make_struct(), reg.name};
            layout.add_model(s);

            for (const auto& opt : reg.options) {
                auto opt_type = option_type(opt);

                s->field_add<Comment>(opt.description); // :((((((
                s->field_add({opt_type, opt.name, opt.size()});

                // Option modifier
                // Later... Need to move to Base, delete all methods and use derived CppBool
                auto opt_param = RVal{opt_type, opt.name};
                auto sf = new IoctlFunction{t::make_void(), reg.name + '_' + "s" + '_' + opt.name, 
                                                set_ioctl_name(reg, opt), opt_param};
                layout.add_model(sf);

                // Option getter
                auto gf = new IoctlFunction{opt_type, reg.name + '_' + "g" + '_' + opt.name,
                                                get_ioctl_name(reg, opt)};
                layout.add_model(gf);
            }

            auto extra = 32 - s->size();
            s->field_add({t::make_uint32(), "align", extra});
        }

        out->serialize(layout);
    }

    void generate_ioctl_enum(const std::vector<Register>& regs, std::unique_ptr<ISerializer>& out) {
        Layout layout;

        auto e = make_anon_enum();
        layout.add_model(e);

        for (const auto& reg : regs) {
            for (const auto& opt : reg.options) {
                // Option modifier
                e->field_add({t::make_empty(), set_ioctl_name(reg, opt)});

                // Option getter
                e->field_add({t::make_empty(), get_ioctl_name(reg, opt)});
            }
        }

        out->serialize(layout);
    }

}; /* generate */