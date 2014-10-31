#include "MethodDeclarationList.h"
#include "MethodDeclaration.h"
#include "Visitor.h"

class MethodDeclarationListMethodDeclaration : MethodDeclarationList
{
public:
	virtual void accept(Visitor & v)
	{
		//v.visit(*this);
	}
private:
	MethodDeclarationList * methodDeclarationList;
	MethodDeclaration & methodDeclaration;

};