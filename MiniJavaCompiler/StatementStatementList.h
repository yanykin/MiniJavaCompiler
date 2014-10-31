#include "Statment.h"
#include "StatementList.h"
#include "Visitor.h"

class StatementStatementList : StatementList
{
public:
	virtual void accept(Visitor & v)
	{
		//v.visit(*this);
	}
private:
	Statment * statment;
	StatementList * statementList;
};