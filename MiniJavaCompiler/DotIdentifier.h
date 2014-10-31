#include "Visitor.h"
#include "Identifier.h"
#include "MethodExpression.h"
#include <string>

class DotIdentifier : MethodExpression
{
public:
	virtual void accept(Visitor & v)
	{
		//v.visit(*this);
	}
private:
	std::string identifier;
};