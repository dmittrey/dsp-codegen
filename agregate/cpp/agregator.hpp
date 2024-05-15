#pragma once

#include "interface/agregator.hpp"

#include "cpp/layout.hpp"
#include "cpp/model.hpp"

#include "type/struct.hpp"
#include "type/void.hpp"

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
                auto sname = CppRVal{Struct(), reg.name};

                auto sdecl = new CppDecl(sname);
                layout.add_model(sdecl); // Decl before function that use sname

                auto s = new CppStructure{sname};
                for (const auto& opt : reg.options) {
                    auto opt_type = opt.type();

                    CppRVal field = {opt_type, opt.name};
                    s->field_add(field);

                    // Option modifier
                    CppRVal sfname = {Void(), reg.name + '_' + 's' + '_' + opt.name};
                    auto sf = new CppFunction{sfname};
                    layout.add_model(sf);

                    // Option getter
                    CppRVal gfname = {opt_type, reg.name + '_' + 'g' + '_' + opt.name};
                    auto gf = new CppFunction{gfname};
                    layout.add_model(gf);
                }

                layout.add_model(s);
            }

            layout.prepare();
            serializer_->serialize(layout);
        }
    };

}; /* Agregate */