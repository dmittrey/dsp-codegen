#include <iostream>
#include <vector>

#include <FlexLexer.h>

#include "reg.hpp"

// here we can return non-zero if lexing is not done inspite of EOF detected
int yyFlexLexer::yywrap() { return 1; }

std::vector<Register> vec;

void parse(Register &reg) {
  vec.push_back(reg);
  std::cout << "Pushed register: " << reg.family << " " << reg.name << " " << reg.addr << " " << reg.offset << " " << reg.type << std::endl;
}

int main() {
  FlexLexer *lexer = new yyFlexLexer;
  while (lexer->yylex() != 0) {
    // do nothing for now, all is in rules
  }

  delete lexer;
}