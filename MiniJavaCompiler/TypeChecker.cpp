#include "TypeChecker.h"
#include <iostream>
#include "GrammaticRules.h"

using namespace std;
using namespace CSymbolsTable;

void CTypeChecker::Visit( const CProgram* node )
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


void CTypeChecker::Visit( const CMainClassDeclaration* node )
{
	// ������� � �����
	currentClass = table->GetClassByName( node->GetClassName() );
	IStatement* statements = node->GetClassStatements();

	if ( statements )
	{
		statements->Accept( this );
	}

	// ������� �� ������
	currentClass = NULL;
}

void CTypeChecker::Visit( const CClassDeclaration* node )
{
	// ������� � �����
	currentClass = table->GetClassByName( node->GetClassName() );

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

	// ������� �� ������
	currentClass = NULL;
}

void CTypeChecker::Visit( const CClassExtendsDeclaration* node )
{
	// ������� � �����
	currentClass = table->GetClassByName( node->GetClassName() );

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

	// ������� �� ������
	currentClass = NULL;
}

void CTypeChecker::Visit( const CClassDeclarationList* node )
{
	IClassDeclaration* classDeclaration = node->GetClassDeclaration();
	classDeclaration->Accept( this );

	IClassDeclaration* nextClassDeclaration = node->GetNextClassDeclaration();
	if ( nextClassDeclaration ) {
		nextClassDeclaration->Accept( this );
	}
}

void CTypeChecker::Visit( const CVariableDeclaration* node )
{
	string name = node->GetName();
	IType* type = node->GetType();

	// ��������� ������� ������������ ������
	Symbol::CSymbol *varType;
	if ( currentMethod ) {
		varType = currentMethod->GetLocalVariableType( node->GetName() );
	}
	else {
		varType = currentClass->GetFieldType( node->GetName() );
	}

	CClassInformation* info = table->GetClassByName( varType->GetString() );

	if ( !IsLastTypeBuiltIn( varType ) && !info ) {
		isCorrect = false;
		if ( currentMethod ) {
			cout << "ERROR (" << node->GetRow() << ", " << node->GetColumn() << "): local variable " << name << " in method " << currentClass->GetName() << "::" << currentMethod->GetName() << ": class " << varType->GetString() << " is not declared" << endl;
		}
		else {
			cout << "ERROR (" << node->GetRow() << ", " << node->GetColumn() << "): field " << name << " in class " << currentClass->GetName() << ": class " << varType->GetString() << " is not declared" << endl;
		}

	}

	type->Accept( this );
}

void CTypeChecker::Visit( const CVariableDeclarationList* node )
{
	IVariableDeclaration* variableDeclaration = node->GetVariableDeclaration();

	CVariableDeclarationList* nextVariableDeclaration = node->GetNextVariableDeclaration();
	if ( nextVariableDeclaration ) {
		nextVariableDeclaration->Accept( this );
	}

	variableDeclaration->Accept( this );
}

void CTypeChecker::Visit( const CMethodDeclaration* node )
{
	// ������� ������ ������
	currentMethod = currentClass->GetMethodByName( node->GetMethodName() );

	// ��������� � ������������� ����
	IType* type = node->GetType();
	type->Accept( this );

	// �������� ������������ ��� ������ � ��������� ��� �������������
	Symbol::CSymbol *returnDeclaredType = currentMethod->GetReturnType();
	if ( !IsLastTypeBuiltIn( returnDeclaredType ) && !( table->GetClassByName( returnDeclaredType->GetString() ) ) ){
		isCorrect = false;
		cout << "ERROR: return type " << returnDeclaredType->GetString() << " in method" << currentClass->GetName() << "::" << currentMethod->GetName() << ": class " << returnDeclaredType->GetString() << " is not declared" << endl;
	}

	// ����������� ����������
	IFormalList* formalList = node->GetFormalList();
	if ( formalList ) {
		formalList->Accept( this );
	}

	// ����������� ��������� ����������
	IVariableDeclaration* localVariableList = node->GetLocalVariablesList();
	if ( localVariableList ) {
		localVariableList->Accept( this );
	}

	IStatement *statementList = node->GetStatements();
	if ( statementList ) {
		statementList->Accept( this );
	}

	IExpression* returnExpression = node->GetReturnExpression();
	returnExpression->Accept( this );

	// ������� �� ������
	currentMethod = NULL;
}

void CTypeChecker::Visit( const CMethodDeclarationList* node )
{
	IMethodDeclaration* methodDeclaraion = node->GetMethodDeclaration();
	methodDeclaraion->Accept( this );

	IMethodDeclaration* nextMethodDeclaration = node->GetNextMethodDeclaration();
	if ( nextMethodDeclaration ) {
		nextMethodDeclaration->Accept( this );
	}
}

void CTypeChecker::Visit( const CFormalList* node )
{
	string name = node->GetParameterName();
	IType* type = node->GetType();

	// ��������� � ����
	type->Accept( this );

	// ��������� ��� ���������
	Symbol::CSymbol* argumentType = currentMethod->GetArgumentType( name );
	if ( !IsLastTypeBuiltIn( argumentType ) && !( table->GetClassByName( argumentType->GetString() ) ) ) {
		isCorrect = false;
		cout << "ERROR (" << node->GetRow() << ", " << node->GetColumn() << "): ";
		cout << "agrument " << name << " in method" << currentClass->GetName() << "::" << currentMethod->GetName() << ": class " << argumentType->GetString() << " is not declared" << endl;
	}
}

void CTypeChecker::Visit( const CFormalRestList* node )
{
	IFormalList* formalRest = node->GetFormalRest();
	formalRest->Accept( this );

	IFormalList* nextFormalRest = node->GetNextFormalRest();
	if ( nextFormalRest ) {
		nextFormalRest->Accept( this );
	}
}

void CTypeChecker::Visit( const CBuiltInType* node )
{
	switch ( node->GetType() )
	{
	case BT_BOOLEAN:
		lastTypeValue = "boolean";
		break;
	case BT_INTEGER:
		lastTypeValue = "int";
		break;
	case BT_INTEGER_ARRAY:
		lastTypeValue = "int[]";
		break;
	default:
		break;
	}
}

void CTypeChecker::Visit( const CUserType* node )
{
	lastTypeValue = node->GetTypeName();
}

void CTypeChecker::Visit( const CStatementList* node )
{
	IStatement* statement = node->GetStatement();
	IStatement* nextStatement = node->GetNextStatement();

	statement->Accept( this );

	if ( nextStatement ) {
		nextStatement->Accept( this );
	}
}

void CTypeChecker::Visit( const CStatementBlock* node )
{
	IStatement* block = node->GetStatementList();
	if ( block ) {
		block->Accept( this );
	}
}

void CTypeChecker::Visit( const CIfStatement* node )
{
	IStatement* trueStatement = node->GetTrueStatement();
	IStatement* falseStatement = node->GetFalseStatement();
	IExpression* condition = node->GetCondition();

	condition->Accept( this );
	// ���������, ��� ������� ����� ����� ���
	if ( lastTypeValue != "boolean" ) {
		cout << "ERROR (" << node->GetRow() << ", " << node->GetColumn() << "): Condition in IF statement should have boolean type" << endl;
		isCorrect = false;
	}

	trueStatement->Accept( this );

	falseStatement->Accept( this );
}

void CTypeChecker::Visit( const CWhileStatement* node )
{
	IExpression* condition = node->GetCondition();
	IStatement* statement = node->GetStatement();

	condition->Accept( this );
	if ( lastTypeValue != "bool" ) {
		cout << "ERROR (" << node->GetRow() << ", " << node->GetColumn() << "): Condition in WHILE statement should have boolean type" << endl;
		isCorrect = false;
	}

	statement->Accept( this );
}

void CTypeChecker::Visit( const CPrintStatement* node )
{
	IExpression *expression = node->GetExpression();
	expression->Accept( this );

	if ( lastTypeValue != "int" ) {
		cout << "ERROR (" << node->GetRow() << ", " << node->GetColumn() << "): PRINT statement can print only integer expressions" << endl;
		isCorrect = false;
	}
}

void CTypeChecker::Visit( const CAssignmentStatement* node )
{
	// ��������� ��� ��������� ����������
	Symbol::CSymbol* leftValueType = currentMethod->GetLocalVariableType( node->GetVariableName() );
	// ���� ����� ��������� ���������� �� �����, �� ���� ��������
	if ( !leftValueType ) {
		leftValueType = currentMethod->GetArgumentType( node->GetVariableName() );
	}
	// ���� � �������� �� �����, �� ���� ���� ������
	if ( !leftValueType ) {
		leftValueType = currentClass->GetFieldType( node->GetVariableName() );
	}

	IExpression *expression = node->GetRightValue();
	expression->Accept( this );

	if ( leftValueType->GetString() != lastTypeValue ) {
		cout << "ERROR (" << node->GetRow() << ", " << node->GetColumn() << "): Left and right values should have equal types" << endl;
		isCorrect = false;
	}

}

void CTypeChecker::Visit( const CArrayElementAssignmentStatement* node )
{
	// ��������� ��� ��������� ���������� (��� ����������� ���������)
	Symbol::CSymbol* leftValueType = currentMethod->GetArgumentType( node->GetArrayName() );
	// ���� ����� �������� �� �����, �� �������� ���������� � ���� ������
	if ( !leftValueType ) {
		leftValueType = currentMethod->GetLocalVariableType( node->GetArrayName() );
	}

	IExpression *expression = node->GetRightValue();
	expression->Accept( this );

	if ( leftValueType->GetString() != "int[]" ) {
		cout << "ERROR (" << node->GetRow() << ", " << node->GetColumn() << "): Left value should have array of integers type" << endl;
		isCorrect = false;
	}
	else if ( lastTypeValue != "int" ) {
		cout << "ERROR (" << node->GetRow() << ", " << node->GetColumn() << "): Right value should have integer type" << endl;
		isCorrect = false;
	}

	IExpression* index = node->GetIndexExpression();
	index->Accept( this );
	// ��������� ��� ������� �������
	if ( lastTypeValue != "int" ) {
		cout << "ERROR (" << node->GetRow() << ", " << node->GetColumn() << "): Index expression should have integer type" << endl;
		isCorrect = false;
	}

}

void CTypeChecker::Visit( const CBinaryOperatorExpression* node )
{
	IExpression* leftValue = node->GetLeftValue();
	IExpression* rightValue = node->GetRightValue();

	leftValue->Accept( this );
	std::string leftValueType = lastTypeValue;

	rightValue->Accept( this );
	std::string rightValueType = lastTypeValue;

	TBinaryOperator oper = node->GetOperator();
	switch ( oper )
	{
	case BO_PLUS:
	case BO_MINUS:
	case BO_LESS:
	case BO_MULTIPLY:
	{
		if ( leftValueType != "int" ) {
			cout << "ERROR (" << node->GetRow() << ", " << node->GetColumn() << "): ";
			cout << "Left agrument must be integer" << endl;
			isCorrect = false;
		}
		else if ( rightValueType != "int" ) {
			cout << "ERROR (" << node->GetRow() << ", " << node->GetColumn() << "): ";
			cout << "Right agrument must be integer" << endl;
			isCorrect = false;
		}
		break;
	}
	case BO_LOGICAL_AND:
	{
		if ( leftValueType != "boolean" ) {
			cout << "ERROR (" << node->GetRow() << ", " << node->GetColumn() << "): ";
			cout << "Left agrument must be boolean" << endl;
			isCorrect = false;
		}
		else if ( rightValueType != "boolean" ) {
			cout << "ERROR (" << node->GetRow() << ", " << node->GetColumn() << "): ";
			cout << "Right agrument must be boolean" << endl;
			isCorrect = false;
		}
		break;
	}
	default:
		break;
	}

	switch ( oper )
	{
	case BO_PLUS:
	case BO_MINUS:
	case BO_MULTIPLY:
		lastTypeValue = "int";
		break;
	case BO_LESS:
	case BO_LOGICAL_AND:
		lastTypeValue = "boolean";
		break;
	default:
		break;
	}
}

void CTypeChecker::Visit( const CIndexAccessExpression* node )
{
	IExpression *arrayExpression = node->GetArrayExpression();
	IExpression *index = node->GetIndex();

	arrayExpression->Accept( this );
	if ( lastTypeValue != "int[]" ) {
		isCorrect = false;
		cout << "ERROR: (" << node->GetRow() << ", " << node->GetColumn() << "): ";
		cout << "array expression must be specified" << endl;
	}

	index->Accept( this );
	if ( lastTypeValue != "int" ) {
		isCorrect = false;
		cout << "ERROR: (" << node->GetRow() << ", " << node->GetColumn() << "): ";
		cout << "index expression must be integer" << endl;
	}

	lastTypeValue = "int";
}

void CTypeChecker::Visit( const CLengthExpression* node )
{
	IExpression* arrayExpression = node->GetArray();
	arrayExpression->Accept( this );

	if ( lastTypeValue != "int[]" ) {
		isCorrect = false;
		cout << "ERROR: length attribute is available only for arrays" << endl;
	}

	lastTypeValue = "int";
}

void CTypeChecker::Visit( const CMethodCallExpression* node )
{
	IExpression* object = node->GetObject();
	IExpression* params = node->GetParams();
	std::string methodName = node->GetMethodName();

	object->Accept( this );
	if ( IsLastTypeBuiltIn( Symbol::CSymbol::GetSymbol( lastTypeValue ) ) ) {
		isCorrect = false;
		cout << "ERROR: class instance is expected" << endl;
	}
	else {
		// ��������� ���
		CClassInformation *info = table->GetClassByName( lastTypeValue );
		if ( !info ) {
			cout << "ERROR: class " << lastTypeValue << " is not declared" << endl;
			isCorrect = false;
		}

		CMethodInformation *methodInfo = info->GetMethodByName( methodName );
		if ( !methodInfo ) {
			cout << "ERROR: method " << lastTypeValue << "::" << methodName << " is not defined" << endl;
			isCorrect = false;
		}
		else {
			if ( params ) {
				params->Accept( this );
			}

			// ���� ����� ��������, �� � �������� ���� ��������� ��������� ��, ��� ���������� �����
			lastTypeValue = methodInfo->GetReturnType()->GetString();
		}
	}

	
}

void CTypeChecker::Visit( const CIntegerOrBooleanExpression* node )
{
	int value = node->GetValue();
	TValueType type = node->GetValueType();

	switch ( type )
	{
	case VT_INTEGER:
		lastTypeValue = "int";
		break;
	case VT_BOOLEAN:
		lastTypeValue = "boolean";
		break;
	default:
		break;
	}
}

void CTypeChecker::Visit( const CIdentifierExpression* node )
{
	// � ������� ����������: ��������� ����������, �������� �������, ���� ������
	Symbol::CSymbol *type = currentMethod->GetLocalVariableType( node->GetVariableName() );
	if ( !type ) {
		type = currentMethod->GetArgumentType( node->GetVariableName() );
	}
	if ( !type ) {
		type = currentClass->GetFieldType( node->GetVariableName() );
	}
	lastTypeValue = type->GetString();
}

void CTypeChecker::Visit( const CThisExpression* node )
{
	lastTypeValue = currentClass->GetName();
}

void CTypeChecker::Visit( const CNewIntegerArrayExpression* node )
{
	IExpression* size = node->GetArraySize();
	size->Accept( this );
}

void CTypeChecker::Visit( const CNewObjectExpression* node )
{
	std::string className = node->GetClass();
	lastTypeValue = className;
}

void CTypeChecker::Visit( const CNegationExpression* node )
{
	IExpression* argument = node->GetArgument();
	argument->Accept( this );

	if ( lastTypeValue != "bool" ) {
		cout << "ERROR: (" << node->GetRow() << ", " << node->GetColumn() << "): ";
		cout << "agrument of negation operator must have boolean type";
	}

	lastTypeValue = "bool";
}

void CTypeChecker::Visit( const CParenthesesExpression* node )
{
	IExpression* expression = node->GetExpression();
	expression->Accept( this );
}

void CTypeChecker::Visit( const CExpressionList* node )
{
	IExpression *expression = node->GetExpression();
	IExpression *nextExpression = node->GetNextExpression();

	expression->Accept( this );

	if ( nextExpression ) {
		nextExpression->Accept( this );
	}
}