#pragma once

#include "interface/agregator.hpp"

#include "cpp/layout.hpp"
#include "cpp/model.hpp"

#include "cpp/type/struct.hpp"
#include "cpp/type/void.hpp"

using namespace Utility;
using namespace Generate;

namespace Agregate {

    struct CppAgregator final : Agregator {
        CppAgregator(std::unique_ptr<IRegParser> &parser, 
                    std::unique_ptr<ISerializer> &serializer) : Agregator(parser, serializer) {}

        void process() const override {
            auto vec = parser_->registers();

            CppLayout layout;

            for (const auto& reg : vec) {
                auto sname = CppRVal{Types::make_struct(), reg.name};

                auto sdecl = new CppDecl(sname);
                layout.add_model(sdecl); // Decl before function that use sname

                auto s = new CppStructure{sname};
                for (const auto& opt : reg.options) {
                    auto opt_type = opt.type();

                    CppRVal field = {opt_type, opt.name};
                    s->field_add(field);

                    // Option modifier
                    // Later... Need to move to Base, delete all methods and use derived CppBool
                    if (opt_type.name == "bool") {
                        auto se = new CppFunction{{Types::make_void(), reg.name + '_' + "enable" + '_' + opt.name}};
                        auto sd = new CppFunction{{Types::make_void(), reg.name + '_' + "disable" + '_' + opt.name}};
                        layout.add_model(se);
                        layout.add_model(sd);
                    } else {
                        auto sf = new CppFunction{{Types::make_void(), reg.name + '_' + 's' + '_' + opt.name}};
                        sf->param_add(CppRVal{opt_type, opt.name});
                        layout.add_model(sf);
                    }

                    // Option getter
                    auto gf = new CppFunction{{opt_type, reg.name + '_' + 'g' + '_' + opt.name}};
                    layout.add_model(gf);
                }

                layout.add_model(s);
            }

            layout.prepare();
            serializer_->serialize(layout);
        }
    };

}; /* Agregate */