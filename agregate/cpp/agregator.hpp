#pragma once

#include "interface/agregator.hpp"
#include "interface/iregparser.hpp"

#include "cpp/layout.hpp"
#include "cpp/comment.hpp"
#include "cpp/structure.hpp"
#include "cpp/function.hpp"
#include "cpp/extra.hpp"

#include "cpp/ioctl/function.hpp"

using namespace Generate::Cpp;
using namespace Generate;

using Parser::IRegParser;

using Utility::Register;
using Utility::Option;

namespace Agregate {

    struct CppAgregator final : IAgregator {
    private:
        const std::unique_ptr<IRegParser> parser_;

    public:
        CppAgregator(std::unique_ptr<IRegParser> &parser) : parser_(std::move(parser)) {}

        void process(std::unique_ptr<ISerializer> &user, std::unique_ptr<ISerializer> &ioctl) const override {
            auto regs_ = parser_->registers();

            CppLayout layout;
            CppLayout ioctl_layout;

            auto e = make_anon_enum();
            ioctl_layout.add_model(e);

            for (const auto& reg : regs_) {
                layout.add_model(new CppComment(reg.description));
                auto s = new CppStructure{Types::make_struct(), reg.name};
                layout.add_model(s);

                for (const auto& opt : reg.options) {
                    auto opt_type = option_type(opt);

                    s->field_add(std::make_unique<CppComment>(opt.description)); // :((((((
                    s->field_add({opt_type, opt.name, opt.size()});

                    // Option modifier
                    // Later... Need to move to Base, delete all methods and use derived CppBool
                    auto opt_param = CppRVal{opt_type, opt.name};
                    auto sf = new IoctlCppFunction{Types::make_void(), reg.name + '_' + "s" + '_' + opt.name, 
                                                    std::string("IOCTL_") + "S_" + opt.name, opt_param};
                    e->field_add({Types::make_empty(), std::string("IOCTL_") + "S_" + opt.name});
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

            user->serialize(layout);
            ioctl->serialize(ioctl_layout);
        }

    private:
        static Type option_type(const Option &opt)
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
    };

}; /* Agregate */