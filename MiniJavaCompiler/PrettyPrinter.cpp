#include "PrettyPrinter.h"

int CPrettyPrinter::Visit( const CProgram *node )
{
	std::cout << "Syntax tree of MiniJava program" << std::endl;
	return 0;
}

int CPrettyPrinter::Visit( const CMainClassDeclaration *node )
{
	std::cout << "Declaration of main class" << std::endl;
	return 0;
}

int CPrettyPrinter::Visit( const CClassDeclaration *node )
{
	std::cout << "Declaration of class" << std::endl;
	return 0;
}

int CPrettyPrinter::Visit( const CClassExtendsDeclaration *node )
{
	std::cout << "Declaration of class that extends from another" << std::endl;
	return 0;
}

int CPrettyPrinter::Visit( const CClassDeclarationList *node )
{
	std::cout << "!!!" << std::endl;
	return 0;
}