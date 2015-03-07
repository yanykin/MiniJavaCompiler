#include "SymbolTableBuilder.h"
#include <iostream>
#include "GrammaticRules.h"

using namespace std;

void CSymbolTableBuilder::Visit( const CProgram* node )
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


void CSymbolTableBuilder::Visit( const CMainClassDeclaration* node )
{
	// Перешли в новый класс, создаём класс
	currentClass = new CSymbolsTable::CClassInformation( node->GetClassName() );

	IStatement* statements = node->GetClassStatements();

	if ( statements )
	{
		statements->Accept( this );
	}

	// После обхода полей и методов класса добавляем его в таблицу
	if ( !table.AddClass( currentClass ) ) {
		cout << "ERROR: duplicate class " << currentClass->GetName() << endl;
		isCorrect = false;
	}
	currentClass = NULL;
}

void CSymbolTableBuilder::Visit( const CClassDeclaration* node )
{
	// Перешли в новый класс, создаём класс
	currentClass = new CSymbolsTable::CClassInformation( node->GetClassName() );

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

	// После обхода полей и методов класса добавляем его в таблицу
	if ( !table.AddClass( currentClass ) ) {
		cout << "ERROR: duplicate class " << currentClass->GetName() << endl;
		isCorrect = false;
	}
	currentClass = NULL;
}

void CSymbolTableBuilder::Visit( const CClassExtendsDeclaration* node )
{
	// Перешли в новый класс, создаём класс
	currentClass = new CSymbolsTable::CClassInformation( node->GetClassName(), node->GetSuperClassName() );

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

	// После обхода полей и методов класса добавляем его в таблицу
	if ( !table.AddClass( currentClass ) ) {
		cout << "ERROR: duplicate class " << currentClass->GetName() << endl;
		isCorrect = false;
	}
	currentClass = NULL;
}

void CSymbolTableBuilder::Visit( const CClassDeclarationList* node )
{
	IClassDeclaration* classDeclaration = node->GetClassDeclaration();
	classDeclaration->Accept( this );

	IClassDeclaration* nextClassDeclaration = node->GetNextClassDeclaration();
	if ( nextClassDeclaration ) {
		nextClassDeclaration->Accept( this );
	}
}

void CSymbolTableBuilder::Visit( const CVariableDeclaration* node )
{
	string name = node->GetName();
	IType* type = node->GetType();

	type->Accept( this );
	// Если находимся внутри какого-то текущего метода, то добавляем как локальную переменную, иначе - как поле класса
	CSymbolsTable::CVariableInformation* var = new CSymbolsTable::CVariableInformation( lastTypeValue, name );
	if ( currentMethod ) {
		if ( !currentMethod->AddLocalVariable( var ) ) {
			cout << "ERROR: duplicate local variable " << var->GetName() << " in method " << currentClass->GetName() << "::" << currentMethod->GetName() << endl;
			isCorrect = false;
		}
	}
	else {
		if ( !currentClass->AddField( var ) ) {
			cout << "ERROR: duplicate field " << var->GetName() << " in class " << currentClass->GetName() << endl;
			isCorrect = false;
		}
	}
}

void CSymbolTableBuilder::Visit( const CVariableDeclarationList* node )
{
	IVariableDeclaration* variableDeclaration = node->GetVariableDeclaration();

	CVariableDeclarationList* nextVariableDeclaration = node->GetNextVariableDeclaration();
	if ( nextVariableDeclaration ) {
		nextVariableDeclaration->Accept( this );
	}

	variableDeclaration->Accept( this );
}

void CSymbolTableBuilder::Visit( const CMethodDeclaration* node )
{
	// Перешли в описание метода
	currentMethod = new CSymbolsTable::CMethodInformation( node->GetMethodName() );

	// Переходим к возвращаемому типу
	IType* type = node->GetType();
	type->Accept( this );
	currentMethod->SetReturnType( Symbol::CSymbol::GetSymbol( lastTypeValue ) );


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

	// После добавления информации о методе добавляем его в класс
	if ( !currentClass->AddMethod( currentMethod ) ) {
		cout << "ERROR: redeclared method " << currentClass->GetName() << "::" << currentMethod->GetName() << endl;
		isCorrect = false;
	}
	currentMethod = NULL;
}

void CSymbolTableBuilder::Visit( const CMethodDeclarationList* node )
{
	IMethodDeclaration* methodDeclaraion = node->GetMethodDeclaration();
	methodDeclaraion->Accept( this );

	IMethodDeclaration* nextMethodDeclaration = node->GetNextMethodDeclaration();
	if ( nextMethodDeclaration ) {
		nextMethodDeclaration->Accept( this );
	}
}

void CSymbolTableBuilder::Visit( const CFormalList* node )
{
	string name = node->GetParameterName();
	IType* type = node->GetType();

	// Переходим к типу

	type->Accept( this );
	CSymbolsTable::CVariableInformation *var = new CSymbolsTable::CVariableInformation( lastTypeValue, name );
	if ( !currentMethod->AddParameter( var ) )
	{
		cout << "ERROR: duplicate argument " << var->GetName() << " in method " << currentClass->GetName() << "::" << currentMethod->GetName() << endl;
		isCorrect = false;
		delete var;
	}
}

void CSymbolTableBuilder::Visit( const CFormalRestList* node )
{
	IFormalList* formalRest = node->GetFormalRest();
	formalRest->Accept( this );

	IFormalList* nextFormalRest = node->GetNextFormalRest();
	if ( nextFormalRest ) {
		nextFormalRest->Accept( this );
	}
}

void CSymbolTableBuilder::Visit( const CBuiltInType* node )
{
	// Для каждого типа мы создаём новую запись

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

void CSymbolTableBuilder::Visit( const CUserType* node )
{
	lastTypeValue = node->GetTypeName();
}

void CSymbolTableBuilder::Visit( const CStatementList* node )
{
	IStatement* statement = node->GetStatement();
	IStatement* nextStatement = node->GetNextStatement();

	statement->Accept( this );

	if ( nextStatement ) {
		nextStatement->Accept( this );
	}
}

void CSymbolTableBuilder::Visit( const CStatementBlock* node )
{
	IStatement* block = node->GetStatementList();
	if ( block ) {
		block->Accept( this );
	}
}

void CSymbolTableBuilder::Visit( const CIfStatement* node )
{
	IStatement* trueStatement = node->GetTrueStatement();
	IStatement* falseStatement = node->GetFalseStatement();
	IExpression* condition = node->GetCondition();

	condition->Accept( this );

	trueStatement->Accept( this );

	falseStatement->Accept( this );
}

void CSymbolTableBuilder::Visit( const CWhileStatement* node )
{
	IExpression* condition = node->GetCondition();
	IStatement* statement = node->GetStatement();

	condition->Accept( this );

	statement->Accept( this );
}

void CSymbolTableBuilder::Visit( const CPrintStatement* node )
{
	IExpression *expression = node->GetExpression();

	expression->Accept( this );
}

void CSymbolTableBuilder::Visit( const CAssignmentStatement* node )
{
	IExpression *expression = node->GetRightValue();

	expression->Accept( this );
}

void CSymbolTableBuilder::Visit( const CArrayElementAssignmentStatement* node )
{
	IExpression* index = node->GetIndexExpression();
	IExpression* value = node->GetRightValue();

	index->Accept( this );

	value->Accept( this );
}

void CSymbolTableBuilder::Visit( const CBinaryOperatorExpression* node )
{
	IExpression* leftValue = node->GetLeftValue();
	IExpression* rightValue = node->GetRightValue();

	leftValue->Accept( this );

	rightValue->Accept( this );
}

void CSymbolTableBuilder::Visit( const CIndexAccessExpression* node )
{
	IExpression *arrayExpression = node->GetArrayExpression();
	IExpression *index = node->GetIndex();

	arrayExpression->Accept( this );

	index->Accept( this );

}

void CSymbolTableBuilder::Visit( const CLengthExpression* node )
{
	IExpression* arrayExpression = node->GetArray();
	arrayExpression->Accept( this );

}

void CSymbolTableBuilder::Visit( const CMethodCallExpression* node )
{
	IExpression* object = node->GetObject();
	IExpression* params = node->GetParams();
	std::string methodName = node->GetMethodName();

	object->Accept( this );

	params->Accept( this );

}

void CSymbolTableBuilder::Visit( const CIntegerOrBooleanExpression* node )
{
	int value = node->GetValue();
	TValueType type = node->GetValueType();
}

void CSymbolTableBuilder::Visit( const CIdentifierExpression* node )
{
}

void CSymbolTableBuilder::Visit( const CThisExpression* node )
{
}

void CSymbolTableBuilder::Visit( const CNewIntegerArrayExpression* node )
{
	IExpression* size = node->GetArraySize();
	size->Accept( this );
}

void CSymbolTableBuilder::Visit( const CNewObjectExpression* node )
{
	std::string className = node->GetClass();
}

void CSymbolTableBuilder::Visit( const CNegationExpression* node )
{
	IExpression* argument = node->GetArgument();
	argument->Accept( this );
}

void CSymbolTableBuilder::Visit( const CParenthesesExpression* node )
{
	IExpression* expression = node->GetExpression();
	expression->Accept( this );
}

void CSymbolTableBuilder::Visit( const CExpressionList* node )
{
	IExpression *expression = node->GetExpression();
	IExpression *nextExpression = node->GetNextExpression();

	expression->Accept( this );

	if ( nextExpression ) {
		nextExpression->Accept( this );
	}
}