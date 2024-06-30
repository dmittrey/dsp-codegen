#pragma once

#include "lexem.hpp"

#include "c/types.hpp"
#include "c/model/function.hpp"
#include "c/model/rval.hpp"

namespace stx {

    namespace c {

        namespace fixedp {

            struct FloatToSignedFixedFunction final : Function {
                FloatToSignedFixedFunction(const Type& ret_type, const std::string &name, const std::string& scale_macro, uint8_t fract_cnt)
                    : Function(ret_type, name) {
                        auto float_param = RVal{t::Double(), "float_val"};

                        gen::Function::params_set<RVal>({float_param});
                        gen::Function::statement_add(Lexem().Return().Braces(ret_type).Braces(
                            Lexem().Braces(float_param.name).Mul().Concat(scale_macro).Braces(std::to_string(fract_cnt))
                        ));
                    }
            };

            struct SignedFixedToFloatFunction final : Function {
                SignedFixedToFloatFunction(const Type& ret_type, const std::string &name, Type fix_type, const std::string& scale_macro, uint8_t fract_cnt)
                    : Function(ret_type, name) {
                        auto fixed_param = RVal{fix_type, "fixed_val"};

                        gen::Function::params_set<RVal>({fixed_param});
                        gen::Function::statement_add(Lexem().Return().Braces(
                            Lexem().Braces(ret_type).Braces(fixed_param.name).Div().Concat(scale_macro).Braces(std::to_string(fract_cnt))
                        ));
                    }
            };

        }; /* fixed-point */

    }; /* c */

}; /* syntax */