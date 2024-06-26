#include "isp/codegen.hpp"

#include "cpp/layout.hpp"
#include "cpp/extra.hpp"
#include "cpp/fixedp/unsigned.hpp"

#include "template/scale_macro.hpp"
#include "template/reg_structure.hpp"
#include "template/opt_modifier.hpp"
#include "template/opt_getter.hpp"

using util::Register;
using util::Option;

using namespace stx::cpp;

namespace gen {

    namespace cpp {

    std::unique_ptr<stx::ILayout> generate_userspace_ctrls(const std::vector<Register>& regs, const std::string& ioctl_enm_path) {
        auto layout = std::make_unique<Layout>();
        layout->add_header(ioctl_enm_path);
        layout->add_header("sys/ioctl.h");

        Layout* fp_layout = new Layout();
        layout->add_model(fp_layout);

        fp_layout->add_model(cpp::tmplt::ScaleMacro());

        for (const auto& reg : regs) {
            layout->add_model(new Comment(reg.description));
            layout->add_model(tmplt::RegStructure(reg));

            for (const auto& opt : reg.options) {
                if (opt.format() == util::FP_UNSIGNED) {
                    fp_layout->add_model(new fixedp::FloatToUnsignedFixedFunction(tmplt::hw_type(opt), tmplt::to_fixed_name(reg, opt),
                                                                    tmplt::ScaleMacroName, opt.fixedp.fract_bits));
                    fp_layout->add_model(new fixedp::UnsignedFixedToFloatFunction(tmplt::log_type(opt), tmplt::to_float_name(reg, opt),
                                                                    tmplt::hw_type(opt), tmplt::ScaleMacroName, opt.fixedp.fract_bits));                               
                }

                // Option modifier
                layout->add_model(cpp::tmplt::OptModifier(reg, opt));

                // Option getter
                layout->add_model(cpp::tmplt::OptGetter(reg, opt));
            }
        }

        return layout;
    }

    std::unique_ptr<stx::ILayout> generate_ioctl_enum(const std::vector<Register>& regs) {
        auto layout = std::make_unique<Layout>();

        auto e = make_anon_enum();
        layout->add_model(e);

        for (const auto& reg : regs) {
            for (const auto& opt : reg.options) {
                // Option modifier
                e->field_add<RVal>({t::Empty(), tmplt::set_ioctl_name(reg, opt)});

                // Option getter
                e->field_add<RVal>({t::Empty(), tmplt::get_ioctl_name(reg, opt)});
            }
        }

        return layout;
    }

    }; /* C++ */

}; /* generate */