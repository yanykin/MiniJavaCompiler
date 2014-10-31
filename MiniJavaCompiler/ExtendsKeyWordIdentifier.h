#include <string>

#include "Visitor.h"
#include "ClassExtends.h"

class ExtendsKeyWordIdentifier :ClassExtends
{
public:
	virtual void accept(Visitor & v)
	{
		//v.visit(*this);
	}
private:
	std::string identifier;
};