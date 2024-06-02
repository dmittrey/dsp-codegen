#include "isp/codegen.hpp"

#include "file/serializer.hpp"

#include "json/regparser.hpp"

using namespace Generate;
using namespace Parse;
using namespace Serialize;

/*

1) Сделать маппинг наконец fp <-> fixp

2) Сделать модуль генератора kernel

*/

int main() {
  std::unique_ptr<IRegParser> parser = make_json_regparser("regtest.json");
  std::unique_ptr<ISerializer> serializer = make_file_serializer("user.outp");
  std::unique_ptr<ISerializer> serializer_ioctl = make_file_serializer("ioctl.outp");
  
  generate_userspace_ctrls(parser->registers(), serializer);
  generate_ioctl_enum(parser->registers(), serializer_ioctl);
}