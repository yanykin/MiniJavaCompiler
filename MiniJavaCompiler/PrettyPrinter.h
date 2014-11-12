/*
* Реализует удобный вывод построенного синтакстического дерева
*/

#pragma once
#include "Visitor.h"

class CPrettyPrinter : public IVisitor
{
public:
	CPrettyPrinter() {};
	int Visit( const CProgram* node );
	int Visit( const CMainClassDeclaration* node );
	int Visit( const CClassDeclaration* node );
	int Visit( const CClassExtendsDeclaration* node );
	int Visit( const CClassDeclarationList* node );
};

