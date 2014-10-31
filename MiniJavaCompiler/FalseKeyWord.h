#pragma once

#include <string>
#include "Visitor.h"
#include "Exp.h"

class FalseKeyWord : Exp
{
public:
	virtual void accept(Visitor & v)
	{
		//v.visit(*this);
	}

};