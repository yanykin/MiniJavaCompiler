#pragma once

#include "Exp.h"



class NotExp : Exp
{
public:
	void accept(Visitor & v) {
		//v.visit(*this);
	}
private:
	Exp & expression;


};