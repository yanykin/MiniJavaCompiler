#include <string>

#include "Visitor.h"
#include "FormalRest.h"
#include "Type.h"

class TypeIdentifierFormalRestList : FormalRest
{
public:
	virtual void accept(Visitor & v)
	{
		//v.visit(*this);
	}
private:
	std::string identifier;
	Type & type;
};