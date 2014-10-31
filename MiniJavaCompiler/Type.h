#include "Visitor.h"

class Type
{
	virtual void accept(Visitor & v) = 0;
};