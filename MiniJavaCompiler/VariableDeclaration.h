#include "Visitor.h"

class VariableDeclaration
{
	virtual void accept(Visitor & v) = 0;
};