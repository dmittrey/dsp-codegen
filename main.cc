#include "cpp/agregator.hpp"

#include "file/serializer.hpp"

#include "json/regparser.hpp"

using namespace Generate;
using namespace Parser;

using namespace Agregate;

/*

Уменьшение сложности, анализ разработанного

Lval

5) Добавить комментарий над структурой(Добавление модели комментария) Comment

6) Добавить выплевывание ioctl в иной файл(доп параметр)

УРА КОДГЕН ГОТОВ

1) Сделать модуль генератора kernel

1) Сделать маппинг наконец fp <-> fixp

LATER...
3) Добавить автогенерацию кернел модуля чтобы работать с регистрами и подставить вызов этих функций уже в код сеттеров геттеров
*/

// Добавить поле
// struct ISP_FLASH_CMD {
// 	uint32_t preflash_on:31;
// 	bool flash_on:1;
// };

int main() {
  std::unique_ptr<IRegParser> parser = std::make_unique<JsonRegParser>("parser/regtest.json");
  std::unique_ptr<ISerializer> serializer = std::make_unique<FileSerializer>("example.inp");
  
  CppAgregator agr = {parser, serializer};
  agr.process();
}