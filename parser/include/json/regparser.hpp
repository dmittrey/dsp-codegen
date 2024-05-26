#pragma once

#include "interface/iregparser.hpp"

namespace Parser {

	std::unique_ptr<IRegParser> make_json_regparser(const std::string& fname);

} /* Parser */