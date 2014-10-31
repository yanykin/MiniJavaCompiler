#pragma once

#include "Visitor.h"

class ExpressionRestList
{
public:
	virtual void accept(Visitor & v) = 0;
};