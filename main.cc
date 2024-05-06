#include <iostream>
#include <memory>
#include <vector>

#include "reglexer.hpp"
#include "model.hpp"

using namespace Generate;

/*
0) Посмотреть лекцию про наследование
1) Поженить отдаваемые парсером значения с кодгеном
2) Поправить парсинг чтобы в рамках регистра были поля, надо менять грамматику => Сделать так чтобы от этого не изменился generate
3) Добавить автогенерацию кернел модуля чтобы работать с регистрами и подставить вызов этих функций уже в код сеттеров геттеров
*/

int main() {
  auto lexer = std::make_unique<RegLexer>();
  while (lexer->yylex() != 0) {
    // do nothing for now, all is in rules
  }
  lexer->print();

  auto stringType = new String();
  auto uintType = new Uint8();
  Structure s;

  RVal s_name;
  s_name.type = stringType;
  s_name.name = "somestruct";

  RVal s_field;
  s_field.type = uintType;
  s_field.name = "somefield";

  s.name = s_name;
  s.fields = {s_field};

  std::cout << s.render() << std::endl;

  // Uint8 type = Uint8{};
  // Getter getter = Getter{};

  // Function unit = {type, {std::make_pair(type, "arg")}, "somename", getter};
  // render(std::cout, unit);
}