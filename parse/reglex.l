/* ------------------------------------------------------------------------- **
 *
 *  Simplest state machine
 *           -------------
 *  start -> |  INITIAL  | --WORD--> | IREG | --WORD--> | IADR |
 *           -------------                                  |
                 /\(Push reg to global storage)             HEX
                 |                                          \/
 *               ------NUM FORMAT----- | IFMT | <--DEC--| IOFS |
 *
 *  Register description: 
 *      FAMILY(WORD) NAME(WORD) ADDR(HEX) OFFSET(DEC) FMT(NUM_FMT)
 * ------------------------------------------------------------------------- */
%option yyclass="RegLexer"
%option c++

%x IREG
%x IADR
%x IOFS
%x IFMT

%{

#include "reglexer.hpp"

%}

WS          [ \t\n\v]+

WORD        [a-z|A-z]+

HEX         0x[0-9]+
DEC         [1-9]*[0-9]+

U_NUM       u
S_NUM       s
U_FP_NUM    u[0-9]+q[0-9]+
S_FP_NUM    s[0-9]+q[0-9]+
SM_FP_NUM   sm[0-9]+q[0-9]+
TC_FP_NUM   t[0-9]+q[0-9]+

%%

{WS}              /* skip blanks and tabs */

{WORD}            { BEGIN IREG;
                    return process_family(); }

<IREG>{WORD}      { BEGIN IADR;
                    return process_name(); }

<IADR>{HEX}       { BEGIN IOFS;
                    return process_address(); }

<IOFS>{DEC}       { BEGIN IFMT;
                    return process_offset(); }

<IFMT>{U_NUM}     { BEGIN INITIAL;
                    return process_type(HEX_UNSIGNED); }
<IFMT>{S_NUM}     { BEGIN INITIAL;
                    return process_type(HEX_SIGNED); }
<IFMT>{U_FP_NUM}  { BEGIN INITIAL; 
                    return process_type(FP_UNSIGNED); }
<IFMT>{S_FP_NUM}  { BEGIN INITIAL;
                    return process_type(FP_SIGNED); }
<IFMT>{SM_FP_NUM} { BEGIN INITIAL; 
                    return process_type(FP_SIGN_MAGNITUDE); }
<IFMT>{TC_FP_NUM} { BEGIN INITIAL; 
                    return process_type(FP_TWOS_COMPLEMENT); }

.                 { return process_unknown(); }

%%

// nothing