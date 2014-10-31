#pragma once

#include "Bracket.h"
#include "Visitor.h"

class OpSCurveBracket : Bracket
{
public:
	virtual void accept(Visitor & v)
	{
		v.visit(*this);
	}
};