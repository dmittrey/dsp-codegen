#pragma once

#include "interface/agregator.hpp"

#include "cpp/layout.hpp"
#include "cpp/model.hpp"

#include "type/struct.hpp"

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
                CppRVal name = {Struct(), reg.name};
                auto s = new CppStructure{name};

                for (const auto& opt : reg.options) {
                    CppRVal field = {opt.type(), opt.name};
                    s->field_add(field);
                }

                layout.add_model(s);
            }

            layout.prepare();
            serializer_->serialize(layout);
        }
    };

}; /* Agregate */