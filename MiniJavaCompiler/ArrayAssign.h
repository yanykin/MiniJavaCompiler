#include "Statment.h"
#include "Exp.h"
#include <string>

class ArrayAssign
{
public:
	virtual void accept(Visitor & v)
	{
		//v.visit(*this);
	}
private:
	Exp & firstExspression;
	Exp & secondExspression;
	std::string identifier;
};