#pragma once

#include "Visitor.h"

class MethodExpression
{
	virtual void accept(Visitor & v) = 0;
};