#include "PrettyPrinter.h"
#include <iostream>
#include "GrammaticRules.h"

using namespace std;

std::string CPrettyPrinter::marginString = "    ";

void CPrettyPrinter::PrintTabs( size_t tabs ) const
{
	for ( size_t i = 0; i < tabs; i++ ) {
		cout << marginString;
	}
}

void CPrettyPrinter::PrintMargin() const
{
	for ( size_t i = 0; i < marginInTabs; i++ ) {
		cout << marginString;
	}
}

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
	else {
		cout << "No other classes" << endl;
	}
}


void CPrettyPrinter::Visit( const CMainClassDeclaration* node )
{
	PrintTabs( 1 );
	cout << "Main class " << node->GetClassName() << endl;
	IStatement* statements = node->GetClassStatements();
	PrintTabs( 2 );
	cout << "Declared methods:" << endl;
	PrintTabs( 3 );
	cout << "main(String[] " << node->GetArgumentName() << ") -> void" << endl;
	if ( statements )
	{
		PrintTabs( 4 );
		statements->Accept( this );
	}
}

void CPrettyPrinter::Visit( const CClassDeclaration* node )
{
	PrintTabs( 1 );
	cout << "Class " << node->GetClassName() << endl;
	IVariableDeclaration* fieldsList = node->GetFieldsList();
	PrintTabs( 2 );
	if ( fieldsList )
	{
		cout << "Declared fields:" << endl;
		fieldsList->Accept( this );
	}
	else {
		cout << "No fields." << endl;
	}

	PrintTabs( 2 );
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
	PrintTabs( 1 );
	cout << endl  << "Class " << node->GetClassName() << " extends from class " << node->GetSuperClassName() << endl;
	IVariableDeclaration* fieldsList = node->GetFieldsList();
	PrintTabs( 2 );
	if ( fieldsList )
	{
		cout << "Declared fields:" << endl;
		fieldsList->Accept( this );
	}
	else {
		cout << "No fields." << endl;
	}

	PrintTabs( 2 );
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

void CPrettyPrinter::Visit( const CClassDeclarationList* node )
{
	IClassDeclaration* classDeclaration = node->GetClassDeclaration();
	classDeclaration->Accept( this );

	IClassDeclaration* nextClassDeclaration = node->GetNextClassDeclaration();
	if ( nextClassDeclaration ) {
		nextClassDeclaration->Accept( this );
	}
}

void CPrettyPrinter::Visit( const CVariableDeclaration* node )
{
	PrintTabs( 3 );
	string name = node->GetName();
	IType* type = node->GetType();
	cout << name << " : ";
	type->Accept( this );

	cout << endl;
}

void CPrettyPrinter::Visit( const CVariableDeclarationList* node )
{
	IVariableDeclaration* variableDeclaration = node->GetVariableDeclaration();
	variableDeclaration->Accept( this );

	CVariableDeclarationList* nextVariableDeclaration = node->GetNextVariableDeclaration();
	if ( nextVariableDeclaration ) {
		nextVariableDeclaration->Accept( this );
	}
}

void CPrettyPrinter::Visit( const CMethodDeclaration* node )
{
	PrintTabs( 3 );
	string name = node->GetMethodName();
	IType* type = node->GetType();
	// cout << "Method ";
	cout << name << "(";
	IFormalList* formalList = node->GetFormalList();
	if ( formalList ) {
		formalList->Accept( this );
	}
	cout << ") -> ";
	type->Accept( this );
	cout << endl;

	IStatement *statementList = node->GetStatements();
	if ( statementList ) {
		SetMargin( 4 );
		statementList->Accept( this );
		cout << endl;
	}
}

void CPrettyPrinter::Visit( const CMethodDeclarationList* node )
{
	IMethodDeclaration* methodDeclaraion = node->GetMethodDeclaration();
	// PrintMargin();
	methodDeclaraion->Accept( this );

	IMethodDeclaration* nextMethodDeclaration = node->GetNextMethodDeclaration();
	if ( nextMethodDeclaration ) {
		nextMethodDeclaration->Accept( this );
	}
}

void CPrettyPrinter::Visit( const CFormalList* node )
{
	string name = node->GetParameterName();
	IType* type = node->GetType();
	
	cout << name << " : ";
	type->Accept( this );
}

void CPrettyPrinter::Visit( const CFormalRestList* node )
{
	IFormalList* formalRest = node->GetFormalRest();
	formalRest->Accept( this );

	IFormalList* nextFormalRest = node->GetNextFormalRest();
	if ( nextFormalRest ) {
		cout << ", ";
		nextFormalRest->Accept( this );
	}
}

void CPrettyPrinter::Visit( const CBuiltInType* node )
{
	// cout << "builtin type ";
	switch ( node->GetType() )
	{
	case BT_BOOLEAN:
		cout << "boolean";
		break;
	case BT_INTEGER:
		cout << "integer";
		break;
	case BT_INTEGER_ARRAY:
		cout << "integer[]";
	default:
		break;
	}
	cout;
}

void CPrettyPrinter::Visit( const CUserType* node )
{
	// cout << "user type ";
	cout << node->GetTypeName();
}

void CPrettyPrinter::Visit( const CStatementList* node )
{
	IStatement* statement = node->GetStatement();
	IStatement* nextStatement = node->GetNextStatement();

	PrintMargin();
	statement->Accept( this );

	if ( nextStatement ) {
		nextStatement->Accept( this );
	}
}

void CPrettyPrinter::Visit( const CStatementBlock* node )
{
	IStatement* block = node->GetStatementList();
	if ( block ) {
		IncreaseMargin();
		block->Accept( this );
		DecreaseMargin();
	}
}

void CPrettyPrinter::Visit( const CIfStatement* node )
{
	cout << "IF statement" << endl;
}

void CPrettyPrinter::Visit( const CWhileStatement* node )
{
	cout << "WHILE statement" << endl;
}

void CPrettyPrinter::Visit( const CPrintStatement* node )
{
	cout << "Print statement" << endl;
}

void CPrettyPrinter::Visit( const CAssignmentStatement* node )
{
	cout << "Assignment statement" << endl;
}

void CPrettyPrinter::Visit( const CArrayElementAssignmentStatement* node )
{
	cout << "Array element assignment statement" << endl;
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