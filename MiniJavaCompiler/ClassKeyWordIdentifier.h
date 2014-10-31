//CLASS_KEYWORD IDENTIFIER ClassExtends '{'  VariableDeclarationList MethodDeclarationList '}'

#include <string>

#include "Visitor.h"
#include "ClassExtends.h"
#include "VariableDeclarationList.h"
#include "MethodDeclarationList.h"
#include "ClassDeclaration.h"

class ClassKeyWordIdentifier : ClassDeclaration
{
public:
	virtual void accept(Visitor & v)
	{
		//v.visit(*this);
	}
private:
	std::string identifier;
	ClassExtends * classExtends;
	VariableDeclarationList * variableDeclarationList;
	MethodDeclarationList * methodDeclarationList;
};