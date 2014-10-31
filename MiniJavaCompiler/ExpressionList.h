#pragma once

#include "Visitor.h"

class ExpressionList
{
	virtual void accept(Visitor & v) = 0;
};