#include "Translate.h"
#include <iostream>
#include "GrammaticRules.h"
#include <cassert>

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

	currentFrame = new Frame::CFrame( Symbol::CSymbol::GetSymbol( currentClass->GetName() + "$main" ) );

	IStatement* statements = node->GetClassStatements();

	if ( statements )
	{
		statements->Accept( this );
	}

	Methods.push_back( std::make_pair( currentFrame, lastWrapper->ToStm() ) );
	// Выходим из класса
	currentClass = nullptr;
	currentFrame = nullptr;
	lastWrapper = nullptr;
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
	currentClass = nullptr;
	lastWrapper = nullptr;
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
	currentClass = nullptr;
	lastWrapper = nullptr;
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

// TODO
void CTranslate::Visit( const CMethodDeclaration* node )
{
	// TODO: в какой-то момент должен строиться фрейм для вызова этой функции
	currentFrame = new Frame::CFrame( Symbol::CSymbol::GetSymbol( currentClass->GetName() + "$" + node->GetMethodName() ) );

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

// TODO
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
	const IRTree::IExp* ifExpr = lastWrapper->ToExp();
	lastWrapper = nullptr;
	Temp::CLabel* trueLabelTemp = new Temp::CLabel();
	Temp::CLabel* falseLabelTemp = new Temp::CLabel();
	Temp::CLabel* endLabelTemp = new Temp::CLabel();
	IRTree::LABEL* trueLabel = new IRTree::LABEL( trueLabelTemp );
	IRTree::LABEL* falseLabel = new IRTree::LABEL( falseLabelTemp );
	IRTree::LABEL* endLabel = new IRTree::LABEL( endLabelTemp );

	trueStatement->Accept( this );
	IRTree::IStm* trueStmHead = new IRTree::SEQ( trueLabel, lastWrapper->ToStm() );
	IRTree::IStm* trueStm = new IRTree::SEQ( trueStmHead, endLabel );
	lastWrapper = nullptr;

	falseStatement->Accept( this );
	IRTree::IStm* falseStmHead = new IRTree::SEQ( falseLabel, lastWrapper->ToStm() );
	IRTree::IStm* falseStm = new IRTree::SEQ( falseStmHead, endLabel );
	lastWrapper = nullptr;
}

void CTranslate::Visit( const CWhileStatement* node )
{
	Temp::CLabel* beforeConditionLabelTemp = new Temp::CLabel();
	Temp::CLabel* inLoopLabelTemp = new Temp::CLabel();
	Temp::CLabel* endLabelTemp = new Temp::CLabel();
	IRTree::LABEL* beforeConditionLabel = new IRTree::LABEL( beforeConditionLabelTemp );
	IRTree::LABEL* inLoopLabel = new IRTree::LABEL( inLoopLabelTemp );
	IRTree::LABEL* endLabel = new IRTree::LABEL( endLabelTemp );

	IExpression* condition = node->GetCondition();
	IStatement* statement = node->GetStatement();

	condition->Accept( this );
	const IRTree::IStm* whileStm = lastWrapper->ToConditional( inLoopLabelTemp, endLabelTemp );
	lastWrapper = nullptr;
	IRTree::IStm* conditionStmHead = new IRTree::SEQ( beforeConditionLabel, whileStm );
	IRTree::IStm* conditionStm = new IRTree::SEQ( conditionStmHead, lastWrapper->ToStm() );

	statement->Accept( this );
	IRTree::IStm* statementStmFirst = new IRTree::SEQ( conditionStm, lastWrapper->ToStm() );
	IRTree::IStm* statementStmSecond = new IRTree::SEQ( statementStmFirst, nullptr /* TODO: JUMP в метку beforeConditionLabel */ );
	IRTree::IStm* statementStm = new IRTree::SEQ( statementStmSecond, endLabel );
	lastWrapper = new Translate::CStmConverter( statementStm );
}

void CTranslate::Visit( const CPrintStatement* node )
{
	IExpression *expression = node->GetExpression();
	expression->Accept( this );
	const IRTree::IExp* exprForPrint = lastWrapper->ToExp();
	lastWrapper = nullptr;

	Temp::CLabel* funcName = new Temp::CLabel( Symbol::CSymbol::GetSymbol( "System.out.println" ) );
	const IRTree::NAME* funcNameTree = new IRTree::NAME( funcName );
	const IRTree::CExpList* args = new IRTree::CExpList( exprForPrint, nullptr );
	const IRTree::IExp* funcCall = new IRTree::CALL( funcNameTree, args );
	lastWrapper = new Translate::CExpConverter( funcCall );
}

void CTranslate::Visit( const CAssignmentStatement* node )
{
	Symbol::CSymbol* varName = Symbol::CSymbol::GetSymbol( node->GetVariableName() );
	const IRTree::IExp* leftExp = currentFrame->FindLocalOrFormal( varName )->GetExp( currentFrame->FramePointer() );

	IExpression *expression = node->GetRightValue();
	expression->Accept( this );
	const IRTree::IExp* rightExp = lastWrapper->ToExp();
	lastWrapper = nullptr;

	lastWrapper = new Translate::CStmConverter( new IRTree::MOVE( leftExp, rightExp ) );
}

void CTranslate::Visit( const CArrayElementAssignmentStatement* node )
{
	// Проверяем тип локальной переменной (или переданного аргумента)
	Symbol::CSymbol* leftValueType = currentMethod->GetArgumentType( node->GetArrayName() );
	// Если такой аргумент не нашли, то пытаемся обратиться к полю класса
	if ( !leftValueType ) {
		leftValueType = currentMethod->GetLocalVariableType( node->GetArrayName() );
	}
	Symbol::CSymbol* varName = Symbol::CSymbol::GetSymbol( node->GetArrayName() );

	IExpression* index = node->GetIndexExpression();
	index->Accept( this );
	const IRTree::IExp* indexExp = new IRTree::MEM( new IRTree::BINOP( IRTree::BO_PLUS, lastWrapper->ToExp(), new IRTree::CONST( 1 ) ) );
	const IRTree::IExp* zeroIndexExp = currentFrame->FindLocalOrFormal( varName )->GetExp( currentFrame->FramePointer() );
	const IRTree::IExp* leftExp = new IRTree::MEM( new IRTree::BINOP( IRTree::BO_PLUS, zeroIndexExp, indexExp ) );

	IExpression *expression = node->GetRightValue();
	expression->Accept( this );
	const IRTree::IExp* rightExp = lastWrapper->ToExp();
	lastWrapper = nullptr;

	lastWrapper = new Translate::CStmConverter( new IRTree::MOVE( leftExp, rightExp ) );
}

void CTranslate::Visit( const CBinaryOperatorExpression* node )
{
	IExpression* leftValue = node->GetLeftValue();
	IExpression* rightValue = node->GetRightValue();

	leftValue->Accept( this );
	const IRTree::IExp* left = lastWrapper->ToExp();
	
	rightValue->Accept( this );
	const IRTree::IExp* right = lastWrapper->ToExp();

	switch( node->GetOperator() ) {
		case TBinaryOperator::BO_PLUS:
			lastWrapper = new Translate::CExpConverter( new IRTree::MEM( new IRTree::BINOP( IRTree::BO_PLUS, left, right ) ) );
			break;
		case TBinaryOperator::BO_MINUS:
			lastWrapper = new Translate::CExpConverter( new IRTree::MEM( new IRTree::BINOP( IRTree::BO_MINUS, left, right ) ) );
			break;
		case TBinaryOperator::BO_MULTIPLY:
			lastWrapper = new Translate::CExpConverter( new IRTree::MEM( new IRTree::BINOP( IRTree::BO_MUL, left, right ) ) );
			break;
		case TBinaryOperator::BO_LESS:
			lastWrapper = new Translate::CRelativeCmpWrapper( IRTree::CJ_LT, left, right );
			break;
		case TBinaryOperator::BO_LOGICAL_AND:
			lastWrapper = new Translate::CFromAndConverter( left, right );
			break;
		default:
			assert( false );;
	}
}

void CTranslate::Visit( const CIndexAccessExpression* node )
{
	IExpression *arrayExpression = node->GetArrayExpression();
	IExpression *index = node->GetIndex();

	arrayExpression->Accept( this );
	const IRTree::IExp* varExp = lastWrapper->ToExp();
	lastWrapper = nullptr;
	
	index->Accept( this );
	const IRTree::IExp* indexExp = new IRTree::BINOP( IRTree::BO_PLUS, new IRTree::MEM( lastWrapper->ToExp() ), new IRTree::CONST( 1 ) );
	lastWrapper = nullptr;
	IRTree::IExp* offset = new IRTree::BINOP( IRTree::BO_MUL, new IRTree::CONST( Frame::CFrame::GetWordSize() ), indexExp );

	// адрес переменной
	lastWrapper = new Translate::CExpConverter( new IRTree::BINOP( IRTree::BO_PLUS, varExp, offset ) );
}

void CTranslate::Visit( const CLengthExpression* node )
{
	IExpression* arrayExpression = node->GetArray();
	arrayExpression->Accept( this );
	const IRTree::IExp* varExp = lastWrapper->ToExp();
	lastWrapper = nullptr;

	const IRTree::IExp* lengthCommandRW = new IRTree::BINOP( IRTree::BO_PLUS, varExp, new IRTree::CONST( 0 ) );

	// временная переменная
	const Temp::CTemp* lengthTemp = new Temp::CTemp();
	const IRTree::TEMP* tempVar = new IRTree::TEMP( lengthTemp );

	const IRTree::MOVE* movingCommand = new IRTree::MOVE( tempVar, varExp );

	// Возвращаем адрес переменной
	lastWrapper = new Translate::CExpConverter( new IRTree::ESEQ( movingCommand, tempVar ) );
}

// При вызове метода должен строиться объект фрейма
void CTranslate::Visit( const CMethodCallExpression* node )
{
	IExpression* object = node->GetObject();
	IExpression* params = node->GetParams();
	std::string methodName = node->GetMethodName();

	object->Accept( this );
	const IRTree::IExp* exprToBeCalled = lastWrapper->ToExp();
	lastWrapper = nullptr;

	// вызываемый метод
	Temp::CLabel* functionLabel = new Temp::CLabel( Symbol::CSymbol::GetSymbol( methodName ) );
	IRTree::NAME* functionName = new IRTree::NAME( functionLabel );

	// TODO: полуить параметры в виде IRTree::CExpList
	IRTree::CExpList* args = nullptr;

	Temp::CTemp* returned = new Temp::CTemp();
	const IRTree::TEMP* returnedTemp = new IRTree::TEMP( returned );

	// TODO: что делать, если ф-ия не возвращает значение
	lastWrapper = new Translate::CExpConverter( new IRTree::ESEQ( new IRTree::MOVE( returnedTemp, new IRTree::CALL( functionName, args ) ), returnedTemp ) );

	currentFrame = nullptr;
}

void CTranslate::Visit( const CIntegerOrBooleanExpression* node )
{
	int value = node->GetValue();
	TValueType type = node->GetValueType();
	if( type == VT_BOOLEAN ) {
		if( value == 0 ) {
			lastWrapper = new Translate::CExpConverter( new IRTree::CONST( 0 ) );
		} else {
			lastWrapper = new Translate::CExpConverter( new IRTree::CONST( 1 ) );
		}
	} else {
		lastWrapper = new Translate::CExpConverter( new IRTree::CONST( value ) );
	}
}

void CTranslate::Visit( const CIdentifierExpression* node )
{
	// Найдем нужную инфу во фрейме
	Symbol::CSymbol* varName = Symbol::CSymbol::GetSymbol( node->GetVariableName() );
	lastWrapper = new Translate::CExpConverter( currentFrame->FindLocalOrFormal( varName )->GetExp( currentFrame->FramePointer() ) );
}

void CTranslate::Visit( const CThisExpression* node )
{
	lastWrapper = new Translate::CExpConverter( new IRTree::TEMP( currentFrame->ThisPointer() ) );
}

void CTranslate::Visit( const CNewIntegerArrayExpression* node )
{
	IExpression* size = node->GetArraySize();
	size->Accept( this );

	const IRTree::IExp* length = lastWrapper->ToExp();
	lastWrapper = nullptr;

	const IRTree::IExp* lengthOfArray = new IRTree::MEM( new IRTree::BINOP( IRTree::BO_PLUS, length, new IRTree::CONST( 1 ) ) );

	// выделение памяти
	Temp::CLabel* mallocLabel = new Temp::CLabel( Symbol::CSymbol::GetSymbol( "malloc" ) );
	const IRTree::NAME* mallocName = new IRTree::NAME( mallocLabel );
	const IRTree::CALL* mallocCall = new IRTree::CALL( mallocName, new IRTree::CExpList( lengthOfArray, nullptr ) );
	Temp::CTemp* resultTemp = new Temp::CTemp();
	const IRTree::TEMP* tempTemp = new IRTree::TEMP( resultTemp );

	// инициализация
	const IRTree::CALL* memSetCall = nullptr;
	const IRTree::SEQ* mallocMoveMemsetHead = new IRTree::SEQ( new IRTree::MOVE( tempTemp, mallocCall ), new IRTree::MOVE( tempTemp, length ) );
	const IRTree::SEQ* mallocMoveMemset = new IRTree::SEQ( mallocMoveMemsetHead, new IRTree::EXP( memSetCall ) );
	lastWrapper = new Translate::CExpConverter( new IRTree::ESEQ( mallocMoveMemset, tempTemp ) );
}

void CTranslate::Visit( const CNewObjectExpression* node )
{
	// выделение памяти
	Temp::CLabel* mallocLabel = new Temp::CLabel( Symbol::CSymbol::GetSymbol( "malloc" ) );

	// TODO: посчитать кол-во полей у класса
	int countOfFields = 255;

	const IRTree::NAME* mallocName = new IRTree::NAME( mallocLabel );
	const IRTree::CALL* mallocCall = new IRTree::CALL( mallocName, new IRTree::CExpList( new IRTree::CONST( countOfFields ), nullptr ) );
	Temp::CTemp* resultTemp = new Temp::CTemp();
	const IRTree::TEMP* tempTemp = new IRTree::TEMP( resultTemp );

	// инициализация
	const IRTree::CALL* memSetCall = nullptr;
	const IRTree::SEQ* mallocMoveMemset = new IRTree::SEQ( new IRTree::MOVE( tempTemp, mallocCall ), new IRTree::EXP( memSetCall ) );
	lastWrapper = new Translate::CExpConverter( new IRTree::ESEQ( mallocMoveMemset, tempTemp ) );
}

void CTranslate::Visit( const CNegationExpression* node )
{
	IExpression* argument = node->GetArgument();
	argument->Accept( this );

	const IRTree::IExp* first = new IRTree::CONST( 0 );
	const IRTree::IExp* second = lastWrapper->ToExp();

	lastWrapper = new Translate::CExpConverter( new IRTree::MEM( new IRTree::BINOP( IRTree::BO_MINUS, first, second ) ) );
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