#pragma once

#include "Type.h"
class TypeString : Type
{
public:
	void accept(Visitor & v) {
		//v.visit(*this);
	}
};
