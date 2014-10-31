#include "Visitor.h"
#include "ExpressionRestList.h"
#include "ExpressionRest.h"

class ExpressionRestExpressionRestList : ExpressionRestList
{
public:
	virtual void accept(Visitor & v)
	{
		//v.visit(*this);
	}
private:
	ExpressionRest & expressionRest;
	ExpressionRestList * expressionRestList;
};