/* ------------------------------------------------------------------------- **
 *
 *  Simplest state machine
 *           -------------
 *  start -> |  INITIAL  | ---WORD---> | INAME | ---WORD---> | IDESC |
 *           -------------                                       |
                 /\(Push opt to global storage)                  SENTENCE
                 |                                               \/
 *               -NUM- | IFMT | <--RWMODE-- | IRWM | <--RANGE-- | IRNG |
 *
 *  Register description: 
 *      REG_NAME(WORD) NAME(WORD) DESC(SENTENCE) BIT_RANGE(RANGE) RWMODE(RWMODE) FMT(NUM_FMT)
 * ------------------------------------------------------------------------- */
%option yyclass="RegLexer"
%option c++

%x IREG

%x IOFS
%x ISIZE

%x INAME
%x IDESC
%x IRNG
%x IRWM
%x IFMT

%{

#include "reglexer.hpp"

%}

WS          [ \t\n\v]+

UP_WORD        [A-Z_]+
WORD           [a-z_]+
SENTENCE       [a-z|A-Z|0-9|[:punct:]| ]+

HEX            0x[0-9]+
DEC            [1-9]*[0-9]+

U_NUM       u
S_NUM       s
U_FP_NUM    u[0-9]+q[0-9]+
S_FP_NUM    s[0-9]+q[0-9]+
SM_FP_NUM   sm[0-9]+q[0-9]+
TC_FP_NUM   t[0-9]+q[0-9]+

%%

{WS}              /* skip blanks and tabs */

{UP_WORD}               { BEGIN IOFS;
                        return process_reg_name(); }
{WORD}:                 { BEGIN IDESC;
                        return process_opt_name(); }

<IREG>{UP_WORD}:        { BEGIN IOFS;
                        return process_reg_name_retry(); }
<IREG>{WORD}:           { BEGIN IDESC;
                        return process_opt_name(); }

<IOFS>{HEX}             { BEGIN ISIZE;
                        return process_reg_offset(); }
<ISIZE>{DEC}            { BEGIN INAME;
                        return process_reg_size(); }

<INAME>{WORD}:         { BEGIN IDESC;
                        return process_opt_name(); }

<IDESC>{SENTENCE};     { BEGIN IRNG;
                        return process_opt_desc(); }

<IRNG>\[{DEC};{DEC}\];  { BEGIN IRWM;
                        return process_opt_range(); }

<IRWM>RO;                { BEGIN IFMT;
                        return process_opt_rwmode(RO); }
<IRWM>WO;                { BEGIN IFMT;
                        return process_opt_rwmode(WO); }
<IRWM>RW;                { BEGIN IFMT;
                        return process_opt_rwmode(RW); }

<IFMT>{U_NUM};           { BEGIN IREG;
                        return process_opt_type(HEX_UNSIGNED); }
<IFMT>{S_NUM};          { BEGIN IREG;
                        return process_opt_type(HEX_SIGNED); }
<IFMT>{U_FP_NUM};        { BEGIN IREG; 
                        return process_opt_type(FP_UNSIGNED); }
<IFMT>{S_FP_NUM};        { BEGIN IREG;
                        return process_opt_type(FP_SIGNED); }
<IFMT>{SM_FP_NUM};       { BEGIN IREG; 
                        return process_opt_type(FP_SIGN_MAGNITUDE); }
<IFMT>{TC_FP_NUM};       { BEGIN IREG; 
                        return process_opt_type(FP_TWOS_COMPLEMENT); }

.                   { return process_unknown(); }

%%

// here we can return non-zero if lexing is not done inspite of EOF detected
int yyFlexLexer::yywrap() { return 1; }