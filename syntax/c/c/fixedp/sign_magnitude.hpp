#pragma once

#include "lexem.hpp"

#include "c/types.hpp"
#include "c/model/function.hpp"
#include "c/model/rval.hpp"

namespace stx {

    namespace c {

        namespace fixedp {

            struct FloatToSignMagnitudeFixedFunction final : Function {
                FloatToSignMagnitudeFixedFunction(const Type& ret_type, const std::string &name, const std::string& scale_macro, uint8_t fract_cnt, uint8_t size)
                    : Function(ret_type, name) {
                        auto float_param = RVal{t::Double(), "float_val"};

                        auto sign_var = RVal{ret_type, "sign"};
                        auto magn_var = RVal{t::Uint32(), "magnitude"};

                        gen::Function::push_header("math.h");
                        gen::Function::params_set<RVal>({float_param});
                        gen::Function::statement_add(
                            Lexem().Concat(sign_var).Equal().CondIfElse(float_param.name + " < 0", "1", "0")
                        );
                        gen::Function::statement_add(Lexem().Concat(magn_var).Equal()
                            .Concat(Lexem().Braces(magn_var.type))
                            .Braces(Lexem().Concat("fabs").Args({float_param.name}).Mul().Concat(scale_macro).Braces(std::to_string(fract_cnt)))
                        );
                        gen::Function::statement_add(
                            Lexem().Return().Braces(
                                Lexem().Concat(sign_var.name).LShift(size - 1)
                            ).LogOr().Concat(magn_var.name)
                        );
                    }
            };

            struct SignMagnitudeFixedToFloatFunction final : Function {
                SignMagnitudeFixedToFloatFunction(const Type& ret_type, const std::string &name, Type fix_type, const std::string& scale_macro, uint8_t fract_cnt, uint8_t size)
                    : Function(ret_type, name) {
                        auto fixed_param = RVal{fix_type, "fixed_val"};

                        auto sign_var = RVal{fix_type, "sign"};
                        auto magn_var = RVal{t::Uint32(), "magnitude"};
                        auto val_var = RVal{ret_type, "val"};

                        gen::Function::params_set<RVal>({fixed_param});
                        gen::Function::statement_add(
                            Lexem().Concat(sign_var).Equal().Concat(fixed_param.name).LogMul().Braces(
                                Lexem().Concat("1").LShift(size - 1)
                            )
                        );
                        gen::Function::statement_add(
                            Lexem().Concat(magn_var).Equal().Concat(fixed_param.name).LogMul().Braces(
                                Lexem().LogInv().Braces(
                                    Lexem().Concat("1").LShift(size - 1)
                                )
                            )
                        );
                        gen::Function::statement_add(
                            Lexem().Concat(val_var).Equal().Braces(ret_type)
                                .Concat(magn_var.name).Div().Concat(scale_macro).Braces(std::to_string(fract_cnt))
                        );
                        gen::Function::statement_add(
                            Lexem().Return().CondIfElse(sign_var.name, '-' + val_var.name, val_var.name)
                        );
                    }
            };

        }; /* fixed-point */

    }; /* c */

}; /* syntax */