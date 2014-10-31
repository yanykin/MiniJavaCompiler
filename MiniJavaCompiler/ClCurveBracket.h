#pragma once

#include "Bracket.h"
#include "Visitor.h"

class ClCurveBracket : Bracket
{
public:
	virtual void accept(Visitor & v)
	{
		v.visit(*this);
	}
};