#include "cpp/agregator.hpp"

#include "file/serializer.hpp"

#include "json/regparser.hpp"

using namespace Generate;
using namespace Parser;

using namespace Agregate;

/*

DRAWIO!!!

6) Добавить выплевывание ioctl в иной файл(доп параметр)

УРА КОДГЕН ГОТОВ

1) Сделать модуль генератора kernel

1) Сделать маппинг наконец fp <-> fixp

LATER...
3) Добавить автогенерацию кернел модуля чтобы работать с регистрами и подставить вызов этих функций уже в код сеттеров геттеров
*/

int main() {
  std::unique_ptr<IRegParser> parser = std::make_unique<JsonRegParser>("parser/regtest.json");
  std::unique_ptr<ISerializer> serializer = std::make_unique<FileSerializer>("example.outp");
  
  CppAgregator agr = {parser, serializer};
  agr.process();
}