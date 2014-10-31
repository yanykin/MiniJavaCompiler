#pragma once

#include "Visitor.h"

class FormalRest
{
	virtual void accept(Visitor & v) = 0;
};