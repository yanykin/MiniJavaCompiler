#pragma once

#include <string>
#include "Visitor.h"
#include "Exp.h"

class IntegerNumber : Exp
{
public:
	int value;
	virtual void accept(Visitor & v)
	{
		//v.visit(*this);
	}

};