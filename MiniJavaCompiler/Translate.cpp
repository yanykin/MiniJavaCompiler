#include "Translate.h"
#include <iostream>
#include "GrammaticRules.h"
#include <cassert>

using namespace std;
using namespace CSymbolsTable;
using namespace Translate;

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
	// ������� � �����
	currentClass = table->GetClassByName( node->GetClassName() );

	currentFrame = new Frame::CFrame( Symbol::CSymbol::GetSymbol( currentClass->GetName() + "$main" ) );

	IStatement* statements = node->GetClassStatements();

	if ( statements )
	{
		statements->Accept( this );
	}

	Methods.push_back( CFragment( currentFrame, lastWrapper->ToStm(), node->GetClassName() + "$main" ) );
	// ������� �� ������
	currentClass = nullptr;
	currentFrame = nullptr;
	lastWrapper = nullptr;
}

void CTranslate::Visit( const CClassDeclaration* node )
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
	currentClass = nullptr;
	lastWrapper = nullptr;
}

void CTranslate::Visit( const CClassExtendsDeclaration* node )
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

	currentFrame->AddLocal( Symbol::CSymbol::GetSymbol( name ) );

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
	// TODO: � �����-�� ������ ������ ��������� ����� ��� ������ ���� �������
	currentFrame = new Frame::CFrame( Symbol::CSymbol::GetSymbol( currentClass->GetName() + "$" + node->GetMethodName() ) );

	// ������� ������ ������
	currentMethod = currentClass->GetMethodByName( node->GetMethodName() );

	// ��������� � ������������� ����
	IType* type = node->GetType();
	type->Accept( this );

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

	const IRTree::IStm* methodStatements = nullptr;
	if ( lastWrapper ) {
		methodStatements = lastWrapper->ToStm();
	} 

	IExpression* returnExpression = node->GetReturnExpression();
	returnExpression->Accept( this );

	const IRTree::IStm* returnStatement = lastWrapper->ToStm();

	const IRTree::IStm* fragremntStatement = nullptr;
	if ( methodStatements ) {
		fragremntStatement = new IRTree::SEQ( methodStatements, returnStatement );
	}
	else {
		fragremntStatement = returnStatement;
	}

	// ��������� �������� ���� � �������
	Methods.push_back( CFragment( currentFrame, fragremntStatement, currentClass->GetName() + "$" + currentMethod->GetName() ) );

	// ������� �� ������
	currentMethod = NULL;
	currentFrame = NULL;
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

	currentFrame->AddFormal( Symbol::CSymbol::GetSymbol( name ) );

	// ��������� � ����
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
	// ������������ ���� � ���� SEQ( fisrt, SEQ( second, .. ) )
	IStatement* statement = node->GetStatement();
	IStatement* nextStatement = node->GetNextStatement();

	statement->Accept( this );
	const IRTree::IStm* head = lastWrapper->ToStm();

	if ( nextStatement ) {
		nextStatement->Accept( this );
		const IRTree::IStm* tail = lastWrapper->ToStm();
		lastWrapper = new Translate::CStmConverter( new IRTree::SEQ( head, tail ) );
	} else {
		lastWrapper = new Translate::CStmConverter( head );
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

	trueStatement->Accept( this );
	const IRTree::IStm* trueStm = nullptr;
	if ( lastWrapper != nullptr ) {
		trueStm = lastWrapper->ToStm();
	}
	lastWrapper = nullptr;

	falseStatement->Accept( this );
	const IRTree::IStm* falseStm = nullptr;
	if ( lastWrapper != nullptr ) {
		falseStm = lastWrapper->ToStm();
	}
	lastWrapper = nullptr;

	condition->Accept( this );
	Temp::CLabel* T = new Temp::CLabel(); // ����� ��� ����� true
	Temp::CLabel* F = new Temp::CLabel(); // ����� ��� ����� false
	Temp::CLabel* D = new Temp::CLabel(); // ����� ����� ���� if

	const IRTree::IStm* jump = lastWrapper->ToConditional( T, F );

	
	lastWrapper = new Translate::CStmConverter( new IRTree::SEQ
		( new IRTree::SEQ
			( new IRTree::SEQ
				( new IRTree::SEQ
					// �������
					( jump,
					// ���� true
					new IRTree::SEQ( new IRTree::LABEL( T ), trueStm ) ),
					new IRTree::JUMP( D ) ),
					// ���� false
					new IRTree::SEQ( new IRTree::LABEL( F ), falseStm ) ),
					new IRTree::LABEL( D ) ) );
}

void CTranslate::Visit( const CWhileStatement* node )
{
	IExpression* condition = node->GetCondition();
	IStatement* statement = node->GetStatement();

	statement->Accept( this );
	const IRTree::IStm* body = lastWrapper->ToStm();
	lastWrapper = nullptr;

	Temp::CLabel* test = new Temp::CLabel(); // ����� ��� �������
	Temp::CLabel* T = new Temp::CLabel(); // ����� ��� ����
	Temp::CLabel* F = new Temp::CLabel(); // ����� ����� ���� while

	condition->Accept( this );
	const IRTree::IStm* jump = lastWrapper->ToConditional( T, F );
	lastWrapper = nullptr;


	lastWrapper = new Translate::CStmConverter( new IRTree::SEQ
		( new IRTree::SEQ
			( new IRTree::SEQ
				// ������� ����� test ��� �������� �������
				( new IRTree::LABEL( test ),
				// �������
				jump  ),
				// ���� true: ����������� ����, JUMP �� ����� test
				( new IRTree::SEQ( new IRTree::LABEL( T ), new IRTree::SEQ(body, new IRTree::JUMP(test) ) ) ) ),
				// ���� false: �����
				new IRTree::LABEL( F ) ) );
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

	lastWrapper = new Translate::CStmConverter( new IRTree::MOVE( new IRTree::MEM( leftExp ), rightExp ) );
}

void CTranslate::Visit( const CArrayElementAssignmentStatement* node )
{
	// ��������� ��� ��������� ���������� (��� ����������� ���������)
	Symbol::CSymbol* leftValueType = currentMethod->GetArgumentType( node->GetArrayName() );
	// ���� ����� �������� �� �����, �� �������� ���������� � ���� ������
	if ( !leftValueType ) {
		leftValueType = currentMethod->GetLocalVariableType( node->GetArrayName() );
	}
	Symbol::CSymbol* varName = Symbol::CSymbol::GetSymbol( node->GetArrayName() );

	const IRTree::IExp* leftExp = currentFrame->FindLocalOrFormal( varName )->GetExp( currentFrame->FramePointer() );
	IExpression* index = node->GetIndexExpression();
	index->Accept( this );
	const IRTree::IExp* indexExp = new IRTree::BINOP( IRTree::BO_PLUS, lastWrapper->ToExp(), new IRTree::CONST( 1 ) );
	const IRTree::IExp* realSize = new IRTree::BINOP( IRTree::BO_MUL, indexExp, new IRTree::CONST( currentFrame->GetWordSize() ) );
	leftExp = new IRTree::MEM( new IRTree::BINOP( IRTree::BO_PLUS, new IRTree::MEM( leftExp ), realSize ) );

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
			lastWrapper = new Translate::CExpConverter( new IRTree::BINOP( IRTree::BO_PLUS, left, right ) );
			break;
		case TBinaryOperator::BO_MINUS:
			lastWrapper = new Translate::CExpConverter( new IRTree::BINOP( IRTree::BO_MINUS, left, right ) );
			break;
		case TBinaryOperator::BO_MULTIPLY:
			lastWrapper = new Translate::CExpConverter( new IRTree::BINOP( IRTree::BO_MUL, left, right ) );
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

	// ����� ����������
	lastWrapper = new Translate::CExpConverter( new IRTree::BINOP( IRTree::BO_PLUS, varExp, offset ) );
}

void CTranslate::Visit( const CLengthExpression* node )
{
	IExpression* arrayExpression = node->GetArray();
	arrayExpression->Accept( this );
	const IRTree::IExp* varExp = lastWrapper->ToExp();
	lastWrapper = nullptr;

	const IRTree::IExp* lengthCommandRW = new IRTree::BINOP( IRTree::BO_PLUS, varExp, new IRTree::CONST( 0 ) );

	// ��������� ����������
	const Temp::CTemp* lengthTemp = new Temp::CTemp();
	const IRTree::TEMP* tempVar = new IRTree::TEMP( lengthTemp );

	const IRTree::MOVE* movingCommand = new IRTree::MOVE( tempVar, varExp );

	// ���������� ����� ����������
	lastWrapper = new Translate::CExpConverter( new IRTree::ESEQ( movingCommand, tempVar ) );
}

void CTranslate::Visit( const CMethodCallExpression* node )
{
	IExpression* object = node->GetObject();
	IExpression* params = node->GetParams();
	std::string methodName = node->GetMethodName();

	object->Accept( this );
	const IRTree::IExp* exprToBeCalled = lastWrapper->ToExp();
	lastWrapper = nullptr;

	// ���������� �����
	Temp::CLabel* functionLabel = new Temp::CLabel( Symbol::CSymbol::GetSymbol( currentClass->GetName() + "$" + methodName ) );
	IRTree::NAME* functionName = new IRTree::NAME( functionLabel );

	expList = nullptr;
	if ( params ) {
		params->Accept( this );
	}
	IRTree::CExpList* args = new IRTree::CExpList(exprToBeCalled, expList );
	

	Temp::CTemp* returned = new Temp::CTemp();
	const IRTree::TEMP* returnedTemp = new IRTree::TEMP( returned );

	// TODO: ��� ������, ���� �-�� �� ���������� ��������
	lastWrapper = new Translate::CExpConverter( new IRTree::ESEQ( new IRTree::MOVE( returnedTemp, new IRTree::CALL( functionName, args ) ), returnedTemp ) );
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
	// ������ ������ ���� �� ������
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

	// ��������� ������
	Temp::CLabel* mallocLabel = new Temp::CLabel( Symbol::CSymbol::GetSymbol( "malloc" ) );
	const IRTree::NAME* mallocName = new IRTree::NAME( mallocLabel );
	const IRTree::CALL* mallocCall = new IRTree::CALL( mallocName, new IRTree::CExpList( lengthOfArray, nullptr ) );
	Temp::CTemp* resultTemp = new Temp::CTemp();
	const IRTree::TEMP* tempTemp = new IRTree::TEMP( resultTemp );

	// �������������
	const IRTree::CALL* memSetCall = nullptr;
	const IRTree::SEQ* mallocMoveMemsetHead = new IRTree::SEQ( new IRTree::MOVE( tempTemp, mallocCall ), new IRTree::MOVE( tempTemp, length ) );
	const IRTree::SEQ* mallocMoveMemset = new IRTree::SEQ( mallocMoveMemsetHead, new IRTree::EXP( memSetCall ) );
	lastWrapper = new Translate::CExpConverter( new IRTree::ESEQ( mallocMoveMemset, tempTemp ) );
}

void CTranslate::Visit( const CNewObjectExpression* node )
{
	// ��������� ������
	Temp::CLabel* mallocLabel = new Temp::CLabel( Symbol::CSymbol::GetSymbol( "malloc" ) );

	CSymbolsTable::CClassInformation* classOfObject = table->GetClassByName( node->GetClass() );
	int countOfFields = classOfObject->GetFieldsCount();

	const IRTree::NAME* mallocName = new IRTree::NAME( mallocLabel );
	const IRTree::CALL* mallocCall = new IRTree::CALL( mallocName, new IRTree::CExpList( new IRTree::CONST( countOfFields ), nullptr ) );
	const Temp::CTemp* resultTemp = currentFrame->ThisPointer();
	const IRTree::TEMP* tempTemp = new IRTree::TEMP( resultTemp );

	// �������������
	const IRTree::MOVE* mallocMoveMemset = new IRTree::MOVE( tempTemp, mallocCall );
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
	const IRTree::IExp* expListHead = lastWrapper->ToExp();

	if ( nextExpression != nullptr ) {
		nextExpression->Accept( this );
	}
	
	expList = new IRTree::CExpList( expListHead, expList );
}