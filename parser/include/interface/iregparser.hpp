#pragma once

#include "register/register.hpp"

namespace Parser {

    struct IRegParser {
        virtual const std::vector<Utility::Register>& registers() const & = 0;
		virtual ~IRegParser() {}
	};

}; /* Parser */