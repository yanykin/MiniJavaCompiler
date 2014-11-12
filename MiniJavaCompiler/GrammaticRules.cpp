#include "GrammaticRules.h"
#include "Visitor.h"

int CProgram::Accept( IVisitor *visitor ) const
{
	visitor->Visit( this );
	mainClassDeclaration->Accept( visitor );
	classDeclarationsList->Accept( visitor );
	return 0;
}

int CMainClassDeclaration::Accept( IVisitor *visitor ) const
{
	return visitor->Visit( this );
}

int CClassDeclaration::Accept( IVisitor *visitor ) const
{
	return visitor->Visit( this );
}

int CClassDeclarationList::Accept( IVisitor *visitor ) const
{
	return visitor->Visit( this );
}

int CClassExtendsDeclaration::Accept( IVisitor *visitor ) const
{
	return visitor->Visit( this );
}