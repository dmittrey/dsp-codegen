#pragma once

#include <vector>

#include "register/register.hpp"

namespace Parser {

    struct IRegParser {
        virtual const std::vector<Register>& registers() const = 0;

		virtual ~IRegParser() {}
	};

}; /* Parser */