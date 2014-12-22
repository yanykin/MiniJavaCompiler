#include "Translate.h"
#include <iostream>
#include "GrammaticRules.h"

using namespace std;
using namespace CSymbolsTable;

void CTranslate::Visit( const CProgram* node )
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


void CTranslate::Visit( const CMainClassDeclaration* node )
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

void CTranslate::Visit( const CClassDeclaration* node )
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

void CTranslate::Visit( const CClassExtendsDeclaration* node )
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

void CTranslate::Visit( const CClassDeclarationList* node )
{
	IClassDeclaration* classDeclaration = node->GetClassDeclaration();
	classDeclaration->Accept( this );

	IClassDeclaration* nextClassDeclaration = node->GetNextClassDeclaration();
	if ( nextClassDeclaration ) {
		nextClassDeclaration->Accept( this );
	}
}

void CTranslate::Visit( const CVariableDeclaration* node )
{
	string name = node->GetName();
	IType* type = node->GetType();

	type->Accept( this );
}

void CTranslate::Visit( const CVariableDeclarationList* node )
{
	IVariableDeclaration* variableDeclaration = node->GetVariableDeclaration();

	CVariableDeclarationList* nextVariableDeclaration = node->GetNextVariableDeclaration();
	if ( nextVariableDeclaration ) {
		nextVariableDeclaration->Accept( this );
	}

	variableDeclaration->Accept( this );
}

void CTranslate::Visit( const CMethodDeclaration* node )
{
	// Заходим внутрь метода
	currentMethod = currentClass->GetMethodByName( node->GetMethodName() );

	// Переходим к возвращаемому типу
	IType* type = node->GetType();
	type->Accept( this );

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

void CTranslate::Visit( const CMethodDeclarationList* node )
{
	IMethodDeclaration* methodDeclaraion = node->GetMethodDeclaration();
	methodDeclaraion->Accept( this );

	IMethodDeclaration* nextMethodDeclaration = node->GetNextMethodDeclaration();
	if ( nextMethodDeclaration ) {
		nextMethodDeclaration->Accept( this );
	}
}

void CTranslate::Visit( const CFormalList* node )
{
	string name = node->GetParameterName();
	IType* type = node->GetType();

	// Переходим к типу
	type->Accept( this );
}

void CTranslate::Visit( const CFormalRestList* node )
{
	IFormalList* formalRest = node->GetFormalRest();
	formalRest->Accept( this );

	IFormalList* nextFormalRest = node->GetNextFormalRest();
	if ( nextFormalRest ) {
		nextFormalRest->Accept( this );
	}
}

void CTranslate::Visit( const CBuiltInType* node )
{
	
}

void CTranslate::Visit( const CUserType* node )
{
	
}

void CTranslate::Visit( const CStatementList* node )
{
	IStatement* statement = node->GetStatement();
	IStatement* nextStatement = node->GetNextStatement();

	statement->Accept( this );

	if ( nextStatement ) {
		nextStatement->Accept( this );
	}
}

void CTranslate::Visit( const CStatementBlock* node )
{
	IStatement* block = node->GetStatementList();
	if ( block ) {
		block->Accept( this );
	}
}

void CTranslate::Visit( const CIfStatement* node )
{
	IStatement* trueStatement = node->GetTrueStatement();
	IStatement* falseStatement = node->GetFalseStatement();
	IExpression* condition = node->GetCondition();

	condition->Accept( this );

	trueStatement->Accept( this );

	falseStatement->Accept( this );
}

void CTranslate::Visit( const CWhileStatement* node )
{
	IExpression* condition = node->GetCondition();
	IStatement* statement = node->GetStatement();

	condition->Accept( this );

	statement->Accept( this );
}

void CTranslate::Visit( const CPrintStatement* node )
{
	IExpression *expression = node->GetExpression();
	expression->Accept( this );
}

void CTranslate::Visit( const CAssignmentStatement* node )
{
	IExpression *expression = node->GetRightValue();
	expression->Accept( this );
}

void CTranslate::Visit( const CArrayElementAssignmentStatement* node )
{
	// Проверяем тип локальной переменной (или переданного аргумента)
	Symbol::CSymbol* leftValueType = currentMethod->GetArgumentType( node->GetArrayName() );
	// Если такой аргумент не нашли, то пытаемся обратиться к полю класса
	if ( !leftValueType ) {
		leftValueType = currentMethod->GetLocalVariableType( node->GetArrayName() );
	}

	IExpression *expression = node->GetRightValue();
	expression->Accept( this );

	IExpression* index = node->GetIndexExpression();
	index->Accept( this );
}

void CTranslate::Visit( const CBinaryOperatorExpression* node )
{
	IExpression* leftValue = node->GetLeftValue();
	IExpression* rightValue = node->GetRightValue();

	leftValue->Accept( this );
	
	rightValue->Accept( this );
}

void CTranslate::Visit( const CIndexAccessExpression* node )
{
	IExpression *arrayExpression = node->GetArrayExpression();
	IExpression *index = node->GetIndex();

	arrayExpression->Accept( this );
	
	index->Accept( this );
}

void CTranslate::Visit( const CLengthExpression* node )
{
	IExpression* arrayExpression = node->GetArray();
	arrayExpression->Accept( this );
}

// При вызове метода должен строиться объект фрейма
void CTranslate::Visit( const CMethodCallExpression* node )
{
	IExpression* object = node->GetObject();
	IExpression* params = node->GetParams();
	std::string methodName = node->GetMethodName();


	// TODO: в какой-то момент должен строиться фрейм для вызова этой функции
	currentFrame = new Frame::CFrame( Symbol::CSymbol::GetSymbol(currentClass->GetName() + ":" + methodName) );

	object->Accept( this );

	params->Accept( this );

	// После работы со фреймом удаляем его
	delete currentFrame;
	currentFrame = NULL;
}

void CTranslate::Visit( const CIntegerOrBooleanExpression* node )
{

}

void CTranslate::Visit( const CIdentifierExpression* node )
{
	
}

void CTranslate::Visit( const CThisExpression* node )
{
	
}

void CTranslate::Visit( const CNewIntegerArrayExpression* node )
{
	IExpression* size = node->GetArraySize();
	size->Accept( this );
}

void CTranslate::Visit( const CNewObjectExpression* node )
{
	
}

void CTranslate::Visit( const CNegationExpression* node )
{
	IExpression* argument = node->GetArgument();
	argument->Accept( this );
}

void CTranslate::Visit( const CParenthesesExpression* node )
{
	IExpression* expression = node->GetExpression();
	expression->Accept( this );
}

void CTranslate::Visit( const CExpressionList* node )
{
	IExpression *expression = node->GetExpression();
	IExpression *nextExpression = node->GetNextExpression();

	expression->Accept( this );

	if ( nextExpression ) {
		nextExpression->Accept( this );
	}
}