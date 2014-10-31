#pragma once

#include "Type.h"
class TypeInt : Type
{
public:
	void accept(Visitor & v) {
		//v.visit(*this);
	}
};
