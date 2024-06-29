#include "isp/codegen.hpp"

#include "file/serializer.hpp"

#include "json/regparser.hpp"

using namespace gen;
using namespace parse;
using namespace serialize;

/*

0) Еще раз обновить архитектуру

1) Сделать маппинг наконец fp <-> fixp

2) Выкатить в интерфейс все прототипы функций

3) Добавить тестов через google tests

+ допилить презу

2) Сделать модуль генератора kernel

*/

int main() {
  std::unique_ptr<IRegParser> parser = make_json_regparser("regtest.json");
  std::unique_ptr<ISerializer> serializer = make_file_serializer("test/user.c");
  std::unique_ptr<ISerializer> serializer_ioctl = make_file_serializer("test/ioctl.h");
  
  auto user_ctrls_layout = c::generate_userspace_ctrls(parser->registers(), "test/ioctl.h");
  auto enum_layout = c::generate_ioctl_enum(parser->registers());

  serializer->serialize(*user_ctrls_layout);
  serializer_ioctl->serialize(*enum_layout);
}