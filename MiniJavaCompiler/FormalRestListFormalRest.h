#include "Visitor.h"
#include "FormalRestList.h"
#include "Type.h"
#include "FormalRest.h"

class FormalRestListFormalRest : FormalRestList
{
public:
	virtual void accept(Visitor & v)
	{
		//v.visit(*this);
	}
private:
	FormalRestList * formalRestList;
	FormalRest * formalRest;
};