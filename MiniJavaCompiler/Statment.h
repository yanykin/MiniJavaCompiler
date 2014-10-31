#include "Visitor.h"

class Statment
{
	virtual void accept(Visitor & v) = 0;
};