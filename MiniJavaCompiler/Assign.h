#include "Statment.h"
#include "Exp.h"
#include "Identifier.h"
#include <string>

class Assign
{
public:
	virtual void accept(Visitor & v)
	{
		//v.visit(*this);
	}
private:
	Exp & exspression;
	std::string identifier;
};