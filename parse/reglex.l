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
 
%option c++

%x IREG
%x IADR
%x IOFS
%x IFMT

%{

using std::cout;
using std::endl;
using std::stoi;

#include "reg.hpp"

void parse(Register &reg);

Register reg;

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

{WORD}            { reg.family = yytext;
                    BEGIN IREG;
                    return 1; }

<IREG>{WORD}      { reg.name = yytext;
                    BEGIN IADR;
                    return 1; }

<IADR>{HEX}       { reg.addr = stoi(yytext, nullptr, 16);
                    BEGIN IOFS;
                    return 1; }

<IOFS>{DEC}       { reg.offset = stoi(yytext);
                    BEGIN IFMT;
                    return 1; }

<IFMT>{U_NUM}     { reg.type = HEX_UNSIGNED;
                    parse(reg);
                    BEGIN INITIAL;
                    return 1; }
<IFMT>{S_NUM}     { reg.type = HEX_SIGNED; 
                    parse(reg);
                    BEGIN INITIAL;
                    return 1; }
<IFMT>{U_FP_NUM}  { reg.type = FP_UNSIGNED; 
                    parse(reg);
                    BEGIN INITIAL; 
                    return 1; }
<IFMT>{S_FP_NUM}  { reg.type = FP_SIGNED;
                    parse(reg);
                    BEGIN INITIAL;
                    return 1; }
<IFMT>{SM_FP_NUM} { reg.type = FP_SIGN_MAGNITUDE;
                    parse(reg); 
                    BEGIN INITIAL; 
                    return 1; }
<IFMT>{TC_FP_NUM} { reg.type = FP_TWOS_COMPLEMENT;
                    parse(reg);
                    BEGIN INITIAL; 
                    return 1; }

.                 { cout << " UNKNOWN <" << yytext << ">" << endl; 
                    return 1; }

%%

// nothing