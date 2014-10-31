#include "Visitor.h"
#include "Statment.h"
#include "StatmentList.h"

class BracketStatementList
{
public:
	virtual void accept(Visitor & v)
	{
		//v.visit(*this);
	}
private:
	StatmentList * statmentList;
};