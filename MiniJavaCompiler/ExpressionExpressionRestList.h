#include "Visitor.h"
#include "Exp.h"
#include "ExpressionRestList.h"

class ExpressionExpressionRestList
{
public:
	virtual void accept(Visitor & v)
	{
		//v.visit(*this);
	}
private:
	Exp & expression;
	ExpressionRestList * expressionRestList;

	
};