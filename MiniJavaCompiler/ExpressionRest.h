#pragma once

#include "Visitor.h"

class ExpressionRest
{
	virtual void accept(Visitor & v) = 0;
};