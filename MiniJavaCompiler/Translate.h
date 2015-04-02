#pragma once
#include "Visitor.h"
#include "Table.h"
#include "Frame.h"
#include "Wrappers.h"
#include <assert.h>
#include <vector>

class CTranslate : public IVisitor
{
public:
	CTranslate(CSymbolsTable::CTable* _table):
		table(_table),
		currentFrame(NULL), currentClass(NULL), currentMethod(NULL), expList(NULL) {
		assert( _table != NULL );
	}

	void Visit( const CProgram* node );
	void Visit( const CMainClassDeclaration* node );
	void Visit( const CClassDeclaration* node );
	void Visit( const CClassExtendsDeclaration* node );
	void Visit( const CClassDeclarationList* node );
	void Visit( const CVariableDeclaration* node );
	void Visit( const CVariableDeclarationList* node );
	void Visit( const CMethodDeclaration* node );
	void Visit( const CMethodDeclarationList* node );
	void Visit( const CFormalList* node );
	void Visit( const CFormalRestList* node );
	void Visit( const CBuiltInType* node );
	void Visit( const CUserType* node );
	void Visit( const CStatementList* node );
	void Visit( const CStatementBlock* node );
	void Visit( const CIfStatement* node );
	void Visit( const CWhileStatement* node );
	void Visit( const CPrintStatement* node );
	void Visit( const CAssignmentStatement* node );
	void Visit( const CArrayElementAssignmentStatement* node );
	void Visit( const CBinaryOperatorExpression* node );
	void Visit( const CIndexAccessExpression* node );
	void Visit( const CLengthExpression* node );
	void Visit( const CMethodCallExpression* node );
	void Visit( const CIntegerOrBooleanExpression* node );
	void Visit( const CIdentifierExpression* node );
	void Visit( const CThisExpression* node );
	void Visit( const CNewIntegerArrayExpression* node );
	void Visit( const CNewObjectExpression* node );
	void Visit( const CNegationExpression* node );
	void Visit( const CParenthesesExpression* node );
	void Visit( const CExpressionList* node );

	// метод представл€ет собой указатель на фрейм и вершину дерева
	std::vector<std::pair< const Frame::CFrame*, const IRTree::IStm* > > Methods;

private:
	CSymbolsTable::CClassInformation* currentClass; // “екущий класс, в котором находитс€ посетитель
	CSymbolsTable::CMethodInformation* currentMethod; // “екущий метод

	CSymbolsTable::CTable* table; // таблица, к которой мы обращаемс€ 
	Frame::CFrame* currentFrame; // текущий фрейм вызова метода
	Translate::ISubtreeWrapper* lastWrapper; // узел, который "возвращаем"

	IRTree::CExpList* expList; // вспомогательна€ переменна€, при помощи которой собираем список из CExp
};