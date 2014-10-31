#include "Visitor.h"

class MethodDeclarationList
{
	virtual void accept(Visitor & v) = 0;
};