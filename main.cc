#include <iostream>
#include <memory>
#include <vector>

#include "reglexer.hpp"
#include "render.hpp"

using namespace Generate;

int main() {
  // auto lexer = std::make_unique<RegLexer>();
  // while (lexer->yylex() != 0) {
    // do nothing for now, all is in rules
  // }
  // lexer->print();

  Uint8 type = Uint8{};
  Getter getter = Getter{};

  Function unit = {type, {std::make_pair(type, "arg")}, "somename", getter};
  render(std::cout, unit);
}