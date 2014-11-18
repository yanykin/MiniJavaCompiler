#include "Visitor.h"
#include "Exp.h"
#include "ExpressionRest.h"

class CommaExpression : ExpressionRest
{
public:
	virtual void accept(Visitor & v)
	{
		//v.visit(*this);
	}
private:
	Exp & expression;
};
