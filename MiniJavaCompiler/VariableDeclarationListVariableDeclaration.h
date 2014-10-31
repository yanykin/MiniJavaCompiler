#include "Visitor.h"
#include "VariableDeclarationList.h"
#include "VariableDeclaration.h"

class VariableDeclarationListVariableDeclaration : VariableDeclarationList
{
public:
	virtual void accept(Visitor & v)
	{
		//v.visit(*this);
	}
private:
	VariableDeclaration & variableDeclaration;
	VariableDeclarationList * variableDeclarationList;

};