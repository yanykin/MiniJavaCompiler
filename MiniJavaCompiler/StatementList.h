#include "Visitor.h"

class StatementList
{
	virtual void accept(Visitor & v) = 0;
};