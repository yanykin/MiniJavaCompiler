#pragma once

#include "Bracket.h"
#include "Visitor.h"

class OpSquareBracket : Bracket
{
public:
	virtual void accept(Visitor & v)
	{
		v.visit(*this);
	}
};