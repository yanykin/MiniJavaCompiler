#include "Program.h"
#include "Visitor.h"
#include "MainClassDeclaration.h"
#include "ClassDeclarationList.h"
class MainClassDeclarationClassDeclarationList : Programm
{
public:
	virtual void accept(Visitor & v)
	{
		//v.visit(*this);
	}
private:
	MainClassDeclaration & mainClassDeclaration;
	ClassDeclarationList * classDeclarationList;
};