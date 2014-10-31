#include "Visitor.h"

class ClassDeclaration
{
	virtual void accept(Visitor & v) = 0;
};