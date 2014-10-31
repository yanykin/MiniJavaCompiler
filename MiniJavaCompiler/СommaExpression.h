#include "Visitor.h"
#include "Exp.h"
#include "ExpressionRest.h"

class ÑommaExpression : ExpressionRest
{
public:
	virtual void accept(Visitor & v)
	{
		//v.visit(*this);
	}
private:
	Exp & expression;
};