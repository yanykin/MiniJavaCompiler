#include <string>

#include "MethodDeclaration.h"
#include "Visitor.h"
#include "Type.h"
#include "FormalList.h"
#include "VariableDeclarationList.h"
#include "StatementList.h"
#include "Exp.h"

//PUBLIC_KEYWORD Type IDENTIFIER '(' FormalList ')' '{' VariableDeclarationList StatementList RETURN_KEYWORD Expression ';' '}'

class PublicKeyWordType : MethodDeclaration
{
public:
	virtual void accept(Visitor & v)
	{
		//v.visit(*this);
	}
private:
	Type & type;
	std::string identifier;
	FormalList * formalList;
	VariableDeclarationList * variableDeclarationList;
	StatementList * statementList;
	Exp & expression;

};