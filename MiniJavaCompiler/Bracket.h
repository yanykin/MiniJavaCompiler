#pragma once

#include "Visitor.h"
#include "Exp.h"

class Bracket
{
	virtual void accept(Visitor & v) = 0;
};