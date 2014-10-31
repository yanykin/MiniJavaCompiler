#pragma once

#include "Visitor.h"

class VariableDeclarationList {
	virtual void accept(Visitor & v) = 0;
};