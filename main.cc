#include "cpp/agregator.hpp"

#include "file/serializer.hpp"

#include "json/regparser.hpp"

using namespace Generate;
using namespace Parser;

using namespace Agregate;

/*

DRAWIO!!!

// Anon structures if possible move to std::optional name of structure

Подумать как нормально передавать внутрь комментарии, чтобы комментить опции(по уму внутрь field_add надо пихать Model)

6) Добавить выплевывание ioctl в иной файл(доп параметр)

УРА КОДГЕН ГОТОВ

1) Сделать модуль генератора kernel

1) Сделать маппинг наконец fp <-> fixp

LATER...
3) Добавить автогенерацию кернел модуля чтобы работать с регистрами и подставить вызов этих функций уже в код сеттеров геттеров
*/

int main() {
  std::unique_ptr<IRegParser> parser = std::make_unique<JsonRegParser>("parser/regtest.json");
  std::unique_ptr<ISerializer> serializer = std::make_unique<FileSerializer>("user.outp");
  std::unique_ptr<ISerializer> serializer_ioctl = std::make_unique<FileSerializer>("ioctl.outp");
  
  CppAgregator agr = {parser};
  agr.process(serializer, serializer_ioctl);
}