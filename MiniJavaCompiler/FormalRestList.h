#pragma once

#include "Visitor.h"

class FormalRestList
{
	virtual void accept(Visitor & v) = 0;
};