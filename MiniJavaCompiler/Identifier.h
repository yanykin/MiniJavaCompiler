#pragma once

#include <string>
#include "Visitor.h"
#include "Exp.h"

class Identifier : Exp
{
public:
	virtual void accept(Visitor & v)
	{
		//v.visit(*this);
	}
private:
	std::string s;

};