#include "Visitor.h"

class MethodDeclaration
{
	virtual void accept(Visitor & v) = 0;
};