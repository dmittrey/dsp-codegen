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
  std::unique_ptr<ISerializer> serializer = make_file_serializer("output/user.c");
  std::unique_ptr<ISerializer> serializer_ioctl_enum = make_file_serializer("output/ioctl.h");

  std::unique_ptr<ISerializer> serializer_priv_ioctls = make_file_serializer("output/priv_ioctl.c");
  
  auto user_ctrls_layout = c::generate_userspace_ctrls(parser->registers(), "ioctl.h");
  auto ioctl_enum_layout = c::generate_ioctl_enum(parser->registers());
  auto priv_ioctls_layout = c::generate_priv_ioctls(parser->registers());

  serializer->serialize(*user_ctrls_layout);
  serializer_ioctl_enum->serialize(*ioctl_enum_layout);
  serializer_priv_ioctls->serialize(*priv_ioctls_layout);
}