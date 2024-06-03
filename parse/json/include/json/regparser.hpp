#pragma once

#include <memory>

#include "iregparser.hpp"

namespace parse {

	std::unique_ptr<IRegParser> make_json_regparser(const std::string& fname);

}; /* parser */