#include <string>
#include "FormalList.h"
#include "Visitor.h"
#include "Type.h"
#include "FormalRestList.h"

class TypeIdentifierFormalRestList : FormalList
{
public:
	virtual void accept(Visitor & v)
	{
		//v.visit(*this);
	}
private:
	Type & type;
	std::string identifier;
	FormalRestList * formalRestList;
};