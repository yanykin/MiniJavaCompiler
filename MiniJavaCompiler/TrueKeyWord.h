#pragma once

#include <string>
#include "Visitor.h"
#include "Exp.h"

class TrueKeyWord : Exp
{
public:
	virtual void accept(Visitor & v)
	{
		//v.visit(*this);
	}

};