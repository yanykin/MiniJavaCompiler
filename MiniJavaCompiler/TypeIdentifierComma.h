#include <string>

#include "VariableDeclaration.h"
#include "Type.h"
#include "Visitor.h"

class TypeIdentifierComma : VariableDeclaration
{
public:
	virtual void accept(Visitor & v)
	{
		//v.visit(*this);
	}
private:
	Type & type;
	std::string identifier;
};