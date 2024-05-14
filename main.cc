#include <iostream>
#include <memory>
#include <vector>

#include "reglexer.hpp"
#include "cpp/layout.hpp"
#include "cpp/model.hpp"
#include "cpp/agregator.hpp"

#include "file/serializer.hpp"

#include "type/string.hpp"

using namespace Generate;
using namespace Parser;

using namespace Agregate;

/*

TODO: Немножко конечно проиграл в том, что типы ориентируются на C++, потом надо переделать

2)Агрегатор дописать и протестировать, обновить main.cc

3)Ребейз проекта

4) Сделать наконец функции
УРА КОДГЕН ГОТОВ

1) Сделать модуль генератора kernel

1) Сделать маппинг наконец fp <-> fixp

LATER...
3) Добавить автогенерацию кернел модуля чтобы работать с регистрами и подставить вызов этих функций уже в код сеттеров геттеров
*/

int main() {
  std::unique_ptr<IRegParser> parser = std::make_unique<JsonRegParser>("parser/regtest.json");
  std::unique_ptr<ISerializer> serializer = std::make_unique<FileSerializer>("example.inp");
  
  CppAgregator agr = {parser, serializer};
  agr.process();
}