#include "Statment.h"
#include "Exp.h"

class SystemOutPrint
{
public:
	virtual void accept(Visitor & v)
	{
		//v.visit(*this);
	}
private:
	Exp & exspression;
};