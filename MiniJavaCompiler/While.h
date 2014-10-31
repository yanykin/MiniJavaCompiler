#include "Statment.h"
#include "Exp.h"

class While
{
public:
	virtual void accept(Visitor & v)
	{
		//v.visit(*this);
	}
private:
	Exp & exspression;
	Statment * statment;

};