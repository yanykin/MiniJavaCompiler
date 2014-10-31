#pragma once

#include "Exp.h"

class BracketExp : Exp
{
public:
	void accept(Visitor & v) {
		//v.visit(*this);
	}
private:
	Exp & Expression;

};