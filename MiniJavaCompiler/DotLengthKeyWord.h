#include "Visitor.h"
#include "MethodExpression.h"

class DotLengthKeyWord : MethodExpression
{
public:
	virtual void accept(Visitor & v)
	{
		//v.visit(*this);
	}
};