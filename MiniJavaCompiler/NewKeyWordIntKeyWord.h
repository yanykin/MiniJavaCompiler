#pragma once

#include <string>
#include "Visitor.h"
#include "Exp.h"

class NewKeyWordIntKeyWord : Exp
{
public:
	virtual void accept(Visitor & v)
	{
		//v.visit(*this);
	}
private:
	Exp &Expression;

};