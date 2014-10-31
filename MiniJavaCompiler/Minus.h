#pragma once

#include "Exp.h"

class Minus : Exp
{
public:
	void accept(Visitor & v) {
		//v.visit(*this);
	}
private:
	Exp & rExpression;
	Exp & lExpression;
};