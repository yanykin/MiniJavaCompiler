#pragma once

#include "Visitor.h"
#include "Exp.h"
#include "MethodExpression.h"

class ExpressionMethodExpression : Exp
{
public:
	virtual void accept(Visitor & v) = 0;
private:
	Exp & expression;
	MethodExpression * methodExpression;
};