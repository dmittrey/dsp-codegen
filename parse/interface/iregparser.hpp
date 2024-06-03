#pragma once

#include "register/register.hpp"

namespace parse {

    struct IRegParser {
        virtual const std::vector<util::Register>& registers() const & noexcept = 0;
		virtual ~IRegParser() {}
	};

}; /* parser */