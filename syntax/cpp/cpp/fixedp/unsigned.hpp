#pragma once

#include "cpp/model/function.hpp"
#include "cpp/model/rval.hpp"

/* Необходимо добавить функцию наследника Function с преобразованием а потом просто вставить в текующую систему */

namespace stx {

    namespace cpp {

        namespace fixedp {

            struct FloatToUnsignedFixedFunction final : Function {
                FloatToUnsignedFixedFunction(Type ret_type, const std::string &name, const std::string& scale_macro, uint8_t fract_cnt)
                    : Function(ret_type, name) {
                        gen::Function::clojure_add<RVal>({
                            {t::make_double(), "float_val"}, 
                            "return (" + ret_type.code() +")((float_val) * " + scale_macro + '(' + std::to_string(fract_cnt) + ')' + ")"
                            });
                    }
            };

            struct UnsignedFixedToFloatFunction final : Function {
                UnsignedFixedToFloatFunction(Type ret_type, const std::string &name, Type fix_type, const std::string& scale_macro, uint8_t fract_cnt)
                    : Function(ret_type, name) {
                        gen::Function::clojure_add<RVal>({
                            {fix_type, "fixed_val"}, 
                            "return (" + ret_type.code() +")((fixed_val) / " + scale_macro + '(' + std::to_string(fract_cnt) + ')' + ")"
                            });
                    }
            };

        }; /* fixed-point */

    }; /* cpp */

}; /* syntax */