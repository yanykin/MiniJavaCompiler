#include "PrettyPrinter.h"
#include <iostream>
#include "GrammaticRules.h"
#include <cassert>

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
	cout << "class " << node->GetClassName() << endl;
	cout << "{" << endl;
	IStatement* statements = node->GetClassStatements();
	PrintTabs( 1 );
	cout << "public static void main(String[] " << node->GetArgumentName() << ")" << endl;
	PrintTabs( 1 ); cout << "{" << endl;
	if ( statements )
	{
		PrintTabs( 2 );
		statements->Accept( this );
	}
	PrintTabs( 1 ); cout << "}" << endl;
	cout << "}" << endl;
}

void CPrettyPrinter::Visit( const CClassDeclaration* node )
{
	cout << "class " << node->GetClassName() << endl;
	cout << "{" << endl;
	IVariableDeclaration* fieldsList = node->GetFieldsList();	
	if ( fieldsList )
	{
		fieldsList->Accept( this );
	}
	
	IMethodDeclaration* methodsList = node->GetMethodsList();
	if ( methodsList )
	{
		methodsList->Accept( this );
	}

	cout << "}" << endl;
}

void CPrettyPrinter::Visit( const CClassExtendsDeclaration* node )
{
	cout << "class " << node->GetClassName() << " extends " << node->GetSuperClassName() << endl;
	cout << "{" << endl;
	IVariableDeclaration* fieldsList = node->GetFieldsList();
	if ( fieldsList )
	{
		fieldsList->Accept( this );
	}

	IMethodDeclaration* methodsList = node->GetMethodsList();
	if ( methodsList )
	{
		methodsList->Accept( this );
	}
	cout << "}" << endl;
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
	string name = node->GetName();
	IType* type = node->GetType();

	type->Accept( this );
	cout << " " << name;
}

void CPrettyPrinter::Visit( const CVariableDeclarationList* node )
{
	IVariableDeclaration* variableDeclaration = node->GetVariableDeclaration();
	
	CVariableDeclarationList* nextVariableDeclaration = node->GetNextVariableDeclaration();
	if ( nextVariableDeclaration ) {
		nextVariableDeclaration->Accept( this );
	}

	PrintTabs( 1 );
	variableDeclaration->Accept( this );
	cout << ";" << endl;
}

void CPrettyPrinter::Visit( const CMethodDeclaration* node )
{
	PrintTabs( 1 );
	string name = node->GetMethodName();
	IType* type = node->GetType();
	// cout << "Method ";
	cout << "public ";
	type->Accept( this );
	cout << " " << name << "(";
	IFormalList* formalList = node->GetFormalList();
	if ( formalList ) {
		formalList->Accept( this );
	}
	cout << ")" << endl;

	PrintTabs( 1 ); cout << "{" << endl;
	IStatement *statementList = node->GetStatements();
	if ( statementList ) {
		SetMargin( 2 );
		statementList->Accept( this );
		cout << endl;
	}
	
	IExpression* returnExpression = node->GetReturnExpression();
	PrintTabs( 2 );
	cout << "return ";
	returnExpression->Accept( this );
	cout << ";" << endl;
	PrintTabs( 1 ); cout << "}" << endl;

	
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
	
	type->Accept( this );
	cout << " " << name;
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
	switch ( node->GetType() )
	{
	case BT_BOOLEAN:
		cout << "boolean";
		break;
	case BT_INTEGER:
		cout << "int";
		break;
	case BT_INTEGER_ARRAY:
		cout << "int[]";
	default:
		break;
	}
}

void CPrettyPrinter::Visit( const CUserType* node )
{
	cout << node->GetTypeName();
}

void CPrettyPrinter::Visit( const CStatementList* node )
{
	IStatement* statement = node->GetStatement();
	IStatement* nextStatement = node->GetNextStatement();

	statement->Accept( this );

	if ( nextStatement ) {
		nextStatement->Accept( this );
	}
}

void CPrettyPrinter::Visit( const CStatementBlock* node )
{
	IStatement* block = node->GetStatementList();
	if ( block ) {

		PrintMargin();
		cout << "{" << endl;

		IncreaseMargin();
		block->Accept( this );
		DecreaseMargin();

		PrintMargin();
		cout << "}" << endl;
	}
}

void CPrettyPrinter::Visit( const CIfStatement* node )
{
	IStatement* trueStatement = node->GetTrueStatement();
	IStatement* falseStatement = node->GetFalseStatement();
	IExpression* condition = node->GetCondition();

	PrintMargin();
	cout << "if (";
	condition->Accept( this );
	cout << ")" << endl;
	PrintMargin();
	cout << "{" << endl;
	IncreaseMargin();
	// PrintMargin();
	trueStatement->Accept( this );
	DecreaseMargin();
	PrintMargin();
	cout << "}" << endl;

	PrintMargin();
	cout << "else" << endl;
	PrintMargin();
	cout << "{" << endl;
	IncreaseMargin();
	// PrintMargin();
	falseStatement->Accept( this );
	DecreaseMargin();
	PrintMargin();
	cout << "}" << endl;
}

void CPrettyPrinter::Visit( const CWhileStatement* node )
{
	IExpression* condition = node->GetCondition();
	IStatement* statement = node->GetStatement();

	PrintMargin();
	cout << "while (";
	condition->Accept( this );
	cout << " )" << endl;

	PrintMargin();
	cout << "{" << endl;
	IncreaseMargin();
	statement->Accept( this );
	DecreaseMargin();
	PrintMargin();
	cout << "}" << endl;
}

void CPrettyPrinter::Visit( const CPrintStatement* node )
{
	IExpression *expression = node->GetExpression();
	PrintMargin();
	cout << "System.out.println(";
	expression->Accept( this );
	cout << ");" << endl;
}

void CPrettyPrinter::Visit( const CAssignmentStatement* node )
{
	IExpression *expression = node->GetRightValue();
	PrintMargin();
	cout << node->GetVariableName() << " = ";
	expression->Accept( this );
	cout << ";" << endl;
}

void CPrettyPrinter::Visit( const CArrayElementAssignmentStatement* node )
{
	IExpression* index = node->GetIndexExpression();
	IExpression* value = node->GetRightValue();
	PrintMargin();
	cout << node->GetArrayName() << "[";
	index->Accept( this );
	cout << "] = ";
	value->Accept( this );
	cout << ";" << endl;
}

void CPrettyPrinter::Visit( const CBinaryOperatorExpression* node )
{
	IExpression* leftValue = node->GetLeftValue();
	IExpression* rightValue = node->GetRightValue();

	leftValue->Accept( this );
	switch ( node->GetOperator() )
	{
	case BO_PLUS:
		cout << " + ";
		break;
	case BO_MINUS:
		cout << " - ";
		break;
	case BO_MULTIPLY:
		cout << " * ";
		break;
	case BO_LESS:
		cout << " < ";
		break;
	case BO_LOGICAL_AND:
		cout << " && ";
		break;
	default:
		assert( false );;
	}
	rightValue->Accept( this );
}

void CPrettyPrinter::Visit( const CIndexAccessExpression* node )
{
	IExpression *arrayExpression = node->GetArrayExpression();
	IExpression *index = node->GetIndex();

	arrayExpression->Accept( this );
	cout << "[ ";
	index->Accept( this );
	cout << " ]";
}

void CPrettyPrinter::Visit( const CLengthExpression* node )
{
	IExpression* arrayExpression = node->GetArray();
	arrayExpression->Accept( this );
	cout << ".length()";
}

void CPrettyPrinter::Visit( const CMethodCallExpression* node )
{
	IExpression* object = node->GetObject();
	IExpression* params = node->GetParams();
	std::string methodName = node->GetMethodName();

	object->Accept( this );
	cout << "." << methodName << "(";
	params->Accept( this );
	cout << ")";
}

void CPrettyPrinter::Visit( const CIntegerOrBooleanExpression* node )
{
	int value = node->GetValue();
	TValueType type = node->GetValueType();
	if ( type == VT_BOOLEAN ) {
		if ( value == 0 ) {
			cout << "false";
		}
		else {
			cout << "true";
		}
	}
	else {
		cout << value;
	}
}

void CPrettyPrinter::Visit( const CIdentifierExpression* node )
{
	std::string name = node->GetVariableName();
	cout << name;
}

void CPrettyPrinter::Visit( const CThisExpression* node )
{
	cout << "this";
}

void CPrettyPrinter::Visit( const CNewIntegerArrayExpression* node )
{
	IExpression* size = node->GetArraySize();
	cout << "int[ ";
	size->Accept( this );
	cout << " ]";
}

void CPrettyPrinter::Visit( const CNewObjectExpression* node )
{
	std::string className = node->GetClass();
	cout << "new " << className << "()";
}

void CPrettyPrinter::Visit( const CNegationExpression* node )
{
	IExpression* argument = node->GetArgument();
	cout << " -";
	argument->Accept( this );
}

void CPrettyPrinter::Visit( const CParenthesesExpression* node )
{
	IExpression* expression = node->GetExpression();
	cout << "( ";
	expression->Accept( this );
	cout << " )";
}

void CPrettyPrinter::Visit( const CExpressionList* node )
{
	IExpression *expression = node->GetExpression();
	IExpression *nextExpression = node->GetNextExpression();

	expression->Accept( this );

	if ( nextExpression ) {
		nextExpression->Accept( this );
	}
}