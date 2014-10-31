#include "Statment.h"
#include "Exp.h"
#include <vector>

class If
{
public:
	virtual void accept(Visitor & v)
	{
		//v.visit(*this);
	}
private:
	Exp & exspression;
	Statment * firstStatment;
	Statment * secondStatment;

};