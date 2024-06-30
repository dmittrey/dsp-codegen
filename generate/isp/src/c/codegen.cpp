#include "isp/codegen.hpp"

#include "c/layout.hpp"
#include "c/model/enum.hpp"

#include "c/fixedp/unsigned.hpp"
#include "c/fixedp/signed.hpp"
#include "c/fixedp/sign_magnitude.hpp"

#include "template/scale_macro.hpp"
#include "template/reg_structure.hpp"
#include "template/opt_modifier.hpp"
#include "template/opt_getter.hpp"

using util::Register;
using util::Option;

using namespace stx::c;

namespace gen {

    namespace c {

        std::unique_ptr<stx::ILayout> generate_userspace_ctrls(const std::vector<Register>& regs, const std::string& ioctl_enm_path) {
            auto layout = std::make_unique<Layout>();
            layout->push_header(ioctl_enm_path);
            layout->push_header("sys/ioctl.h");

            Layout* fp_layout = new Layout();
            layout->add_model(fp_layout);

            fp_layout->add_model(tmplt::ScaleMacro());

            for (const auto& reg : regs) {
                layout->add_model(new Comment(reg.description));
                layout->add_model(tmplt::RegStructure(reg));

                for (const auto& opt : reg.options) {
                    if (opt.format() == util::FP_UNSIGNED) {
                        fp_layout->add_model(new fixedp::FloatToUnsignedFixedFunction(tmplt::s_hw_type(opt), tmplt::to_fixed_name(reg, opt),
                                                                        tmplt::ScaleMacroName, opt.fixedp.fract_bits));
                        fp_layout->add_model(new fixedp::UnsignedFixedToFloatFunction(tmplt::log_type(opt), tmplt::to_float_name(reg, opt),
                                                                        tmplt::s_hw_type(opt), tmplt::ScaleMacroName, opt.fixedp.fract_bits));       
                    } else if (opt.format() == util::FP_SIGNED || opt.format() == util::FP_TWOS_COMPLEMENT) {
                        fp_layout->add_model(new fixedp::FloatToSignedFixedFunction(tmplt::s_hw_type(opt), tmplt::to_fixed_name(reg, opt),
                                                                        tmplt::ScaleMacroName, opt.fixedp.fract_bits));
                        fp_layout->add_model(new fixedp::SignedFixedToFloatFunction(tmplt::log_type(opt), tmplt::to_float_name(reg, opt),
                                                                        tmplt::s_hw_type(opt), tmplt::ScaleMacroName, opt.fixedp.fract_bits));
                    } else if (opt.format() == util::FP_SIGN_MAGNITUDE) {
                        fp_layout->add_model(new fixedp::FloatToSignMagnitudeFixedFunction(tmplt::s_hw_type(opt), tmplt::to_fixed_name(reg, opt),
                                                                        tmplt::ScaleMacroName, opt.fixedp.fract_bits, opt.size(), tmplt::u_hw_type(opt)));
                        fp_layout->add_model(new fixedp::SignMagnitudeFixedToFloatFunction(tmplt::log_type(opt), tmplt::to_float_name(reg, opt),
                                                                        tmplt::s_hw_type(opt), tmplt::ScaleMacroName, opt.fixedp.fract_bits, opt.size(), tmplt::u_hw_type(opt)));
                    }

                    // Option modifier
                    if (reg.mode != util::RWMode::RO)
                        layout->add_model(tmplt::OptModifier(reg, opt));

                    // Option getter
                    if (reg.mode != util::RWMode::WO)
                        layout->add_model(tmplt::OptGetter(reg, opt));
                }
            }

            return layout;
        }

        std::unique_ptr<stx::ILayout> generate_ioctl_enum(const std::vector<Register>& regs) {
            auto layout = std::make_unique<Layout>();

            auto e = new Enum();
            layout->add_model(e);

            for (const auto& reg : regs) {
                for (const auto& opt : reg.options) {
                    // Option modifier
                    if (reg.mode != util::RWMode::RO)
                        e->field_add<std::string>({tmplt::set_ioctl_name(reg, opt)});

                    // Option getter
                    if (reg.mode != util::RWMode::WO)
                        e->field_add<std::string>({tmplt::get_ioctl_name(reg, opt)});
                }
            }

            return layout;
        }

    }; /* C */

}; /* generate */