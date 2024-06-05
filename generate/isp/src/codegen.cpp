#include "isp/codegen.hpp"

#include "cpp/layout.hpp"
#include "cpp/extra.hpp"

#include "cpp/model/comment.hpp"
#include "cpp/model/function.hpp"
#include "cpp/model/rval.hpp"
#include "cpp/model/structure.hpp"
#include "cpp/model/macro.hpp"

#include "cpp/fixedp/unsigned.hpp"

using util::Register;
using util::Option;

using serialize::ISerializer;

using stx::gen::Type;

using namespace stx::cpp;

namespace gen {

    static Type log_type(const Option& o);
    static Type hw_type(const Option& o);

    static std::string set_ioctl_name(Register reg, Option opt) {
        return std::string("IOCTL") + '_' + reg.name + "_S_" + opt.name;
    }

    static std::string get_ioctl_name(Register reg, Option opt) {
        return std::string("IOCTL") + '_' + reg.name + "_G_" + opt.name;
    }

    void generate_userspace_ctrls(const std::vector<Register>& regs, std::unique_ptr<ISerializer>& out, const std::string& ioctl_enm_path) {
        Layout layout;
        layout.add_header(ioctl_enm_path);

        Layout* fp_layout = new Layout();
        layout.add_model(fp_layout);

        auto scale_macro = new Macro("SCALE_FACTOR");
        scale_macro->add_clojure({"frac_bits", "1 << frac_bits"});
        fp_layout->add_model(scale_macro);

        for (const auto& reg : regs) {
            layout.add_model(new Comment(reg.description));
            auto s = new Structure{t::make_struct(), reg.name};
            layout.add_model(s);

            for (const auto& opt : reg.options) {
                auto opt_param_type = log_type(opt);

                if (opt.format() == util::FP_UNSIGNED) {
                    fp_layout->add_model(new fixedp::FloatToUnsignedFixedFunction(hw_type(opt), reg.name + '_' + opt.name + "_to_fixed",
                                                                    "SCALE_FACTOR", opt.fixedp.fract_bits));
                    fp_layout->add_model(new fixedp::UnsignedFixedToFloatFunction(log_type(opt), reg.name + '_' + opt.name + "_to_float",
                                                                    hw_type(opt), "SCALE_FACTOR", opt.fixedp.fract_bits));                               
                }

                s->field_add<Comment>(opt.description);
                s->field_add({hw_type(opt), opt.name, opt.hw_size()});

                // Option modifier
                auto opt_param_s = RVal{opt_param_type, opt.name};
                auto sf = new Function{t::make_cint(), reg.name + '_' + "s" + '_' + opt.name};
                if (opt.format() == util::FP_UNSIGNED) {
                    sf->clojure_add<RVal>({opt_param_s, 
                                        hw_type(opt).code() + " val = " + reg.name + '_' + opt.name + "_to_fixed(" + opt.name + ")"});
                    sf->clojure_add<RVal>({{t::make_cint(), "fd"}, 
                                            "return ioctl(fd, " + set_ioctl_name(reg, opt) + ", " + "val" + ")"});
                } else {
                    sf->param_add<RVal>({t::make_cint(), "fd"});
                    sf->clojure_add<RVal>({opt_param_s,
                                            "return ioctl(fd, " + set_ioctl_name(reg, opt) + ", " + opt_param_s.name + ")"});
                }
                layout.add_model(sf);


                // Option getter
                auto opt_param_g = RVal{t::make_ptr(opt_param_type), opt.name + "_p"};
                auto gf = new Function{t::make_cint(), reg.name + '_' + "g" + '_' + opt.name};
                if (opt.format() == util::FP_UNSIGNED) {
                    gf->method_add(hw_type(opt).code() + " val");
                    gf->clojure_add<RVal>({{t::make_cint(), "fd"}, 
                                            t::make_cint().code() + " ret = ioctl(fd, " + get_ioctl_name(reg, opt) + ", " + "&val" + ")"});
                    gf->clojure_add<RVal>({opt_param_g, 
                                            "*" + opt_param_g.name + " = " + reg.name + '_' + opt.name + "_to_float(" + "val" + ")"});
                    gf->method_add("return ret");
                } else {
                    gf->param_add<RVal>({t::make_cint(), "fd"});
                    gf->clojure_add<RVal>({opt_param_g,
                                            "return ioctl(fd, " + get_ioctl_name(reg, opt) + ", " + opt_param_g.name + ")"});
                }

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

    static Type log_type(const Option& o) {
        auto bits_cnt = o.log_size();
        if (o.format() == util::HEX_UNSIGNED) {
            if (bits_cnt == 1)
                return t::make_bool();
            else if (bits_cnt <= 8)
                return t::make_uint8();
            else if (bits_cnt <= 16)
                return t::make_uint16();
            else if (bits_cnt <= 32)
                return t::make_uint32();
            else
                return t::make_uint64();
        } else if (o.format() == util::HEX_SIGNED) {
            if (bits_cnt == 1)
                return t::make_bool();
            else if (bits_cnt <= 8)
                return t::make_int8();
            else if (bits_cnt <= 16)
                return t::make_int16();
            else if (bits_cnt <= 32)
                return t::make_int32();
            else
                return t::make_int64();
        } else {
            return t::make_double();
        }
    }

    static Type hw_type(const Option& o) {
        auto size = o.hw_size();
        if (size == 1)
            return t::make_bool();
        else if (size <= 8)
            return t::make_uint8();
        else if (size <= 16)
            return t::make_uint16();
        else if (size <= 32)
            return t::make_uint32();
        else
            return t::make_uint64();
    }

}; /* generate */