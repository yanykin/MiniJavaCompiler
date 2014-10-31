#pragma once

#include "Type.h"
class TypeBoolean : Type
{
public:
	void accept(Visitor & v) {
		//v.visit(*this);
	}
};
