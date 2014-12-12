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
	// Заходим в класс
	currentClass = table->GetClassByName( node->GetClassName() );
	IStatement* statements = node->GetClassStatements();

	if ( statements )
	{
		statements->Accept( this );
	}

	// Выходим из класса
	currentClass = NULL;
}

void CTypeChecker::Visit( const CClassDeclaration* node )
{
	// Заходим в класс
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

	// Выходим из класса
	currentClass = NULL;
}

void CTypeChecker::Visit( const CClassExtendsDeclaration* node )
{
	// Заходим в класс
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

	// Выходим из класса
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

	// Проверяем наличие определённого класса
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
			cout << "ERROR: local variable " << name << " in method " << currentClass->GetName() << "::" << currentMethod->GetName() << ": class " << varType->className << " is not declared" << endl;
		}
		else {
			cout << "ERROR: field " << name << " in class " << currentClass->GetName() << ": class " << varType->className << " is not declared" << endl;
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
	// Заходим внутрь метода
	currentMethod = currentClass->GetMethodByName( node->GetMethodName() );

	// Переходим к возвращаемому типу
	IType* type = node->GetType();
	type->Accept( this );

	// Получаем возвращаемый тип метода и проверяем его существование
	CType *returnDeclaredType = currentMethod->GetReturnType();
	if ( returnDeclaredType->type == VAR_TYPE_CLASS && !( table->GetClassByName( returnDeclaredType->className ) ) ){
		isCorrect = false;
		cout << "ERROR: return type in method" << currentClass->GetName() << "::" << currentMethod->GetName() << ": class " << returnDeclaredType->className << " is not declared" << endl;
	}

	// Определение параметров
	IFormalList* formalList = node->GetFormalList();
	if ( formalList ) {
		formalList->Accept( this );
	}

	// Определение локальных переменных
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

	// Выходим из метода
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

	// Переходим к типу
	type->Accept( this );

	// Проверяем тип аргумента
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
	// Для каждого типа мы создаём новую запись

}

void CTypeChecker::Visit( const CUserType* node )
{

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

	trueStatement->Accept( this );

	falseStatement->Accept( this );
}

void CTypeChecker::Visit( const CWhileStatement* node )
{
	IExpression* condition = node->GetCondition();
	IStatement* statement = node->GetStatement();

	condition->Accept( this );

	statement->Accept( this );
}

void CTypeChecker::Visit( const CPrintStatement* node )
{
	IExpression *expression = node->GetExpression();

	expression->Accept( this );
}

void CTypeChecker::Visit( const CAssignmentStatement* node )
{
	IExpression *expression = node->GetRightValue();

	expression->Accept( this );
}

void CTypeChecker::Visit( const CArrayElementAssignmentStatement* node )
{
	IExpression* index = node->GetIndexExpression();
	IExpression* value = node->GetRightValue();

	index->Accept( this );

	value->Accept( this );
}

void CTypeChecker::Visit( const CBinaryOperatorExpression* node )
{
	IExpression* leftValue = node->GetLeftValue();
	IExpression* rightValue = node->GetRightValue();

	leftValue->Accept( this );

	rightValue->Accept( this );
}

void CTypeChecker::Visit( const CIndexAccessExpression* node )
{
	IExpression *arrayExpression = node->GetArrayExpression();
	IExpression *index = node->GetIndex();

	arrayExpression->Accept( this );

	index->Accept( this );

}

void CTypeChecker::Visit( const CLengthExpression* node )
{
	IExpression* arrayExpression = node->GetArray();
	arrayExpression->Accept( this );

}

void CTypeChecker::Visit( const CMethodCallExpression* node )
{
	IExpression* object = node->GetObject();
	IExpression* params = node->GetParams();
	std::string methodName = node->GetMethodName();

	object->Accept( this );

	params->Accept( this );

}

void CTypeChecker::Visit( const CIntegerOrBooleanExpression* node )
{
	int value = node->GetValue();
	TValueType type = node->GetValueType();
}

void CTypeChecker::Visit( const CIdentifierExpression* node )
{
}

void CTypeChecker::Visit( const CThisExpression* node )
{
}

void CTypeChecker::Visit( const CNewIntegerArrayExpression* node )
{
	IExpression* size = node->GetArraySize();
	size->Accept( this );
}

void CTypeChecker::Visit( const CNewObjectExpression* node )
{
	std::string className = node->GetClass();
}

void CTypeChecker::Visit( const CNegationExpression* node )
{
	IExpression* argument = node->GetArgument();
	argument->Accept( this );
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