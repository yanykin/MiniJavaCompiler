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
	// ??????? ? ?????
	currentClass = table->GetClassByName( node->GetClassName() );
	IStatement* statements = node->GetClassStatements();

	if ( statements )
	{
		statements->Accept( this );
	}

	// ??????? ?? ??????
	currentClass = NULL;
}

void CTypeChecker::Visit( const CClassDeclaration* node )
{
	// ??????? ? ?????
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

	// ??????? ?? ??????
	currentClass = NULL;
}

void CTypeChecker::Visit( const CClassExtendsDeclaration* node )
{
	// ??????? ? ?????
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

	// ??????? ?? ??????
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

	// ????????? ??????? ????????????? ??????
	CType *varType;
	if ( currentMethod ) {
		varType = currentMethod->GetLocalVariableType( node->GetName() );
	}
	else {
		varType = currentClass->GetFieldType( node->GetName() );
	}
	
	CClassInformation* info = table->GetClassByName( varType->className );

	if ( varType->type == VAR_TYPE_CLASS && !info ) {
		isCorrect = false;
		if ( currentMethod ) {
			cout << "ERROR (" << node->GetRow() << ", " << node->GetColumn() <<  "): local variable " << name << " in method " << currentClass->GetName() << "::" << currentMethod->GetName() << ": class " << varType->className << " is not declared" << endl;
		}
		else {
			cout << "ERROR (" << node->GetRow() << ", " << node->GetColumn() << "): field " << name << " in class " << currentClass->GetName() << ": class " << varType->className << " is not declared" << endl;
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
	// ??????? ?????? ??????
	currentMethod = currentClass->GetMethodByName( node->GetMethodName() );

	// ????????? ? ????????????? ????
	IType* type = node->GetType();
	type->Accept( this );

	// ???????? ???????????? ??? ?????? ? ????????? ??? ?????????????
	CType *returnDeclaredType = currentMethod->GetReturnType();
	if ( returnDeclaredType->type == VAR_TYPE_CLASS && !( table->GetClassByName( returnDeclaredType->className ) ) ){
		isCorrect = false;
		cout << "ERROR: return type in method" << currentClass->GetName() << "::" << currentMethod->GetName() << ": class " << returnDeclaredType->className << " is not declared" << endl;
	}

	// ??????????? ??????????
	IFormalList* formalList = node->GetFormalList();
	if ( formalList ) {
		formalList->Accept( this );
	}

	// ??????????? ????????? ??????????
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

	// ??????? ?? ??????
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

	// ????????? ? ????
	type->Accept( this );

	// ????????? ??? ?????????
	CType* argumentType = currentMethod->GetArgumentType( name );
	if ( argumentType->type == VAR_TYPE_CLASS && !(table->GetClassByName(argumentType->className)) ) {
		isCorrect = false;
		cout << "ERROR: agrument " << name << " in method" << currentClass->GetName() << "::" << currentMethod->GetName() << ": class " << argumentType->className << " is not declared" << endl;
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
		lastTypeValue.type = VAR_TYPE_BOOLEAN;
		break;
	case BT_INTEGER:
		lastTypeValue.type = VAR_TYPE_INTEGER;
		break;
	case BT_INTEGER_ARRAY:
		lastTypeValue.type = VAR_TYPE_INTEGER_ARRAY;
		break;
	default:
		break;
	}
}

void CTypeChecker::Visit( const CUserType* node )
{
	lastTypeValue.type = VAR_TYPE_CLASS;
	lastTypeValue.className = node->GetTypeName();
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
	// ?????????, ??? ??????? ????? ????? ???
	if ( lastTypeValue.type != VAR_TYPE_BOOLEAN ) {
		cout << "ERROR (" << node->GetRow() << ", " << node->GetColumn() << "): condition in IF statement should have boolean type" << endl;
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
	if ( lastTypeValue.type != VAR_TYPE_BOOLEAN ) {
		cout << "ERROR (" << node->GetRow() << ", " << node->GetColumn() << "): condition in WHILE statement should have boolean type" << endl;
		isCorrect = false;
	}

	statement->Accept( this );
}

void CTypeChecker::Visit( const CPrintStatement* node )
{
	IExpression *expression = node->GetExpression();
	if ( lastTypeValue.type != VAR_TYPE_INTEGER ) {
		cout << "ERROR (" << node->GetRow() << ", " << node->GetColumn() << "): PRINT statement can print only integer expressions" << endl;
		isCorrect = false;
	}
	expression->Accept( this );
}

void CTypeChecker::Visit( const CAssignmentStatement* node )
{
	// ????????? ??? ????????? ??????????
	CType* leftValueType = currentMethod->GetLocalVariableType( node->GetVariableName() );
	// ???? ????? ????????? ?????????? ?? ?????, ?? ???? ????????
	if ( !leftValueType ) {
		leftValueType = currentMethod->GetArgumentType( node->GetVariableName() );
	} 
	// ???? ? ???????? ?? ?????, ?? ???? ???? ??????
	if ( !leftValueType ) {
		leftValueType = currentClass->GetFieldType( node->GetVariableName() );
	}

	IExpression *expression = node->GetRightValue();
	expression->Accept( this );

	if ( ( leftValueType->type != lastTypeValue.type ) || ( leftValueType->type == lastTypeValue.type && leftValueType->className != lastTypeValue.className ) ) {
		cout << "ERROR (" << node->GetRow() << ", " << node->GetColumn() << "): left and right values should have equal types" << endl;
		isCorrect = false;
	}

}

void CTypeChecker::Visit( const CArrayElementAssignmentStatement* node )
{
	// ????????? ??? ????????? ?????????? (??? ??????????? ?????????)
	CType* leftValueType = currentMethod->GetArgumentType( node->GetArrayName() );
	// ???? ????? ???????? ?? ?????, ?? ???????? ?????????? ? ???? ??????
	if ( !leftValueType ) {
		leftValueType = currentMethod->GetLocalVariableType( node->GetArrayName() );
	}

	IExpression *expression = node->GetRightValue();
	expression->Accept( this );

	if ( leftValueType->type != VAR_TYPE_INTEGER_ARRAY ) {
		cout << "ERROR (" << node->GetRow() << ", " << node->GetColumn() << "): left value should have array of integers type" << endl;
		isCorrect = false;
	}
	else if ( lastTypeValue.type != VAR_TYPE_INTEGER ) {
		cout << "ERROR (" << node->GetRow() << ", " << node->GetColumn() << "): right value should have integer type" << endl;
		isCorrect = false;
	}

	IExpression* index = node->GetIndexExpression();
	index->Accept( this );
	// ????????? ??? ??????? ???????
	if ( lastTypeValue.type != VAR_TYPE_INTEGER ) {
		cout << "ERROR (" << node->GetRow() << ", " << node->GetColumn() << "): index expression should have integer type" << endl;
		isCorrect = false;
	}
	
}

void CTypeChecker::Visit( const CBinaryOperatorExpression* node )
{
	IExpression* leftValue = node->GetLeftValue();
	IExpression* rightValue = node->GetRightValue();

	leftValue->Accept( this );
	TVariableType leftValueType = lastTypeValue.type;

	rightValue->Accept( this );
	TVariableType rightValueType = lastTypeValue.type;

	TBinaryOperator oper = node->GetOperator();
	switch ( oper )
		{
		case BO_PLUS:
		case BO_MINUS:
		case BO_LESS:
		case BO_MULTIPLY:
		case BO_LOGICAL_AND:
		{
			if ( leftValueType != VAR_TYPE_INTEGER ) {
				cout << "ERROR (" << node->GetRow() << ", " << node->GetColumn() << "): ";
				cout << "Left agrument must be integer" << endl;
				isCorrect = false;
			}
			else if ( rightValueType != VAR_TYPE_INTEGER ) {
				cout << "ERROR (" << node->GetRow() << ", " << node->GetColumn() << "): ";
				cout << "Right agrument must be integer" << endl;
				isCorrect = false;
			}
		}
		default:
			break;
		}

	switch ( oper )
	{
	case BO_PLUS:
	case BO_MINUS:
	case BO_MULTIPLY:
		lastTypeValue.type = VAR_TYPE_INTEGER;
		break;
	case BO_LESS:
	case BO_LOGICAL_AND:
		lastTypeValue.type = VAR_TYPE_BOOLEAN;
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
	if ( lastTypeValue.type != VAR_TYPE_INTEGER_ARRAY ) {
		isCorrect = false;
		cout << "ERROR: (" << node->GetRow() << ", " << node->GetColumn() << "): ";
		cout << "array expression must be specified" << endl;
	}

	index->Accept( this );
	if ( lastTypeValue.type != VAR_TYPE_INTEGER ) {
		isCorrect = false;
		cout << "ERROR: (" << node->GetRow() << ", " << node->GetColumn() << "): ";
		cout << "index expression must be integer" << endl;
	}

	lastTypeValue.type = VAR_TYPE_INTEGER;
}

void CTypeChecker::Visit( const CLengthExpression* node )
{
	IExpression* arrayExpression = node->GetArray();
	arrayExpression->Accept( this );

	if ( lastTypeValue.type != VAR_TYPE_INTEGER_ARRAY ) {
		isCorrect = false;
		cout << "ERROR: lentgh attribute is available only for arrays" << endl;
	}

	lastTypeValue.type = VAR_TYPE_INTEGER;
}

void CTypeChecker::Visit( const CMethodCallExpression* node )
{
	IExpression* object = node->GetObject();
	IExpression* params = node->GetParams();
	std::string methodName = node->GetMethodName();

	object->Accept( this );
	if ( lastTypeValue.type != VAR_TYPE_CLASS ) {
		isCorrect = false;
		cout << "ERROR: class instance is expected" << endl;
	}
	else {
		// ????????? ???
		CClassInformation *info = table->GetClassByName( lastTypeValue.className );
		if ( !info ) {
			cout << "ERROR: class " << lastTypeValue.className << " is not declared" << endl;
			isCorrect = false;
		}
		
		CMethodInformation *methodInfo = info->GetMethodByName( methodName );
		if ( !methodInfo ) {
			cout << "ERROR: method " << lastTypeValue.className << "::" << methodName << " is not defined" << endl;
			isCorrect = false;
		}
	}

	params->Accept( this );

}

void CTypeChecker::Visit( const CIntegerOrBooleanExpression* node )
{
	int value = node->GetValue();
	TValueType type = node->GetValueType();

	switch ( type )
	{
	case VT_INTEGER:
		lastTypeValue.type = VAR_TYPE_INTEGER;
		break;
	case VT_BOOLEAN:
		lastTypeValue.type = VAR_TYPE_BOOLEAN;
		break;
	default:
		break;
	}
}

void CTypeChecker::Visit( const CIdentifierExpression* node )
{
	// ? ??????? ???????????: ????????? ??????????, ???????? ???????, ???? ??????
	CType *type = currentMethod->GetLocalVariableType( node->GetVariableName() );
	if ( !type ) {
		type = currentMethod->GetArgumentType( node->GetVariableName() );
	}
	if ( !type ) {
		type = currentClass->GetFieldType( node->GetVariableName() );
	}
	lastTypeValue = *type;
}

void CTypeChecker::Visit( const CThisExpression* node )
{
	lastTypeValue.type = VAR_TYPE_CLASS;
	lastTypeValue.className = currentClass->GetName();
}

void CTypeChecker::Visit( const CNewIntegerArrayExpression* node )
{
	IExpression* size = node->GetArraySize();
	size->Accept( this );
}

void CTypeChecker::Visit( const CNewObjectExpression* node )
{
	std::string className = node->GetClass();
	lastTypeValue.type = VAR_TYPE_CLASS;
	lastTypeValue.className = className;
}

void CTypeChecker::Visit( const CNegationExpression* node )
{
	IExpression* argument = node->GetArgument();
	argument->Accept( this );

	if ( lastTypeValue.type != VAR_TYPE_BOOLEAN ) {
		cout << "ERROR: (" << node->GetRow() << ", " << node->GetColumn() << "): ";
		cout << "agrument of negation operator must have boolean type";
	}

	lastTypeValue.type = VAR_TYPE_BOOLEAN;
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