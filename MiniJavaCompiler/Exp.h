#pragma once

#include "Visitor.h"

class Exp
{
	virtual void accept(Visitor & v) = 0;
	int value; //не уверен, что нужно
};