#include "PrettyPrinter.h"
#include <iostream>
#include "GrammaticRules.h"

using namespace std;

void CPrettyPrinter::Visit( const CProgram* node )
{
	cout << "=== Program on MiniJava ===" << endl;
	IMainClassDeclaration* mainClass = node->GetMainClassDeclaration();
	if ( mainClass )
	{
		mainClass->Accept( this );
	}

	IClassDeclaration* classDeclarations = node->GetClassDeclarationsList();
	if ( classDeclarations )
	{
		classDeclarations->Accept( this );
	}
}


void CPrettyPrinter::Visit( const CMainClassDeclaration* node )
{
	cout << "Main class " << node->GetClassName() << endl;
	IStatement* statements = node->GetClassStatements();
	if ( statements )
	{
		statements->Accept( this );
	}
}

void CPrettyPrinter::Visit( const CClassDeclaration* node )
{
	cout << "Class " << node->GetClassName() << endl;
	IVariableDeclaration* fieldsList = node->GetFieldsList();
	if ( fieldsList )
	{
		cout << "Declared fields:" << endl;
		fieldsList->Accept( this );
	}
	else {
		cout << "No fields." << endl;
	}

	IMethodDeclaration* methodsList = node->GetMethodsList();
	if ( methodsList )
	{
		cout << "Declared methods:" << endl;
		methodsList->Accept( this );
	}
	else {
		cout << "No methods." << endl;
	}
}

void CPrettyPrinter::Visit( const CClassExtendsDeclaration* node )
{

}

void CPrettyPrinter::Visit( const CClassDeclarationList* node )
{

}

void CPrettyPrinter::Visit( const CVariableDeclaration* node )
{

}

void CPrettyPrinter::Visit( const CVariableDeclarationList* node )
{

}

void CPrettyPrinter::Visit( const CMethodDeclaration* node )
{

}

void CPrettyPrinter::Visit( const CMethodDeclarationList* node )
{

}

void CPrettyPrinter::Visit( const CFormalList* node )
{

}

void CPrettyPrinter::Visit( const CFormalRestList* node )
{

}

void CPrettyPrinter::Visit( const CBuiltInType* node )
{

}

void CPrettyPrinter::Visit( const CUserType* node )
{

}

void CPrettyPrinter::Visit( const CStatementList* node )
{

}

void CPrettyPrinter::Visit( const CStatementBlock* node )
{

}

void CPrettyPrinter::Visit( const CIfStatement* node )
{

}

void CPrettyPrinter::Visit( const CWhileStatement* node )
{

}

void CPrettyPrinter::Visit( const CPrintStatement* node )
{

}

void CPrettyPrinter::Visit( const CAssignmentStatement* node )
{

}

void CPrettyPrinter::Visit( const CArrayElementAssignmentStatement* node )
{

}

void CPrettyPrinter::Visit( const CBinaryOperatorExpression* node )
{

}

void CPrettyPrinter::Visit( const CIndexAccessExpression* node )
{

}

void CPrettyPrinter::Visit( const CLengthExpression* node )
{

}

void CPrettyPrinter::Visit( const CMethodCallExpression* node )
{

}

void CPrettyPrinter::Visit( const CIntegerOrBooleanExpression* node )
{

}

void CPrettyPrinter::Visit( const CIdentifierExpression* node )
{

}

void CPrettyPrinter::Visit( const CThisExpression* node )
{

}

void CPrettyPrinter::Visit( const CNewIntegerArrayExpression* node )
{

}

void CPrettyPrinter::Visit( const CNewObjectExpression* node )
{

}

void CPrettyPrinter::Visit( const CNegationExpression* node )
{

}

void CPrettyPrinter::Visit( const CParenthesesExpression* node )
{

}

void CPrettyPrinter::Visit( const CExpressionList* node )
{

}