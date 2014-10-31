#include "Visitor.h"

class FormalList
{
	virtual void accept(Visitor & v) = 0;
};