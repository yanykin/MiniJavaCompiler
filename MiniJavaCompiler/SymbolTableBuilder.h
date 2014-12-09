/*
* Реализация паттерна "Посетитель" для построения таблицы символов программы
*/
#pragma once
#include "Visitor.h"
#include "Table.h"

class CSymbolTableBuilder : public IVisitor
{
public:
	CSymbolTableBuilder(): isCorrect(true), currentClass( NULL ), currentMethod( NULL ) { };
	
	bool IsTableCorrect() const { return isCorrect; };

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


private:
	bool isCorrect; // Флаг, означающий, что таблица символов у нас построена верно

	CSymbolsTable::CClassInformation* currentClass; // Текущий класс, в котором находится посетитель
	CSymbolsTable::CMethodInformation* currentMethod; // Текущий метод
	CSymbolsTable::CType lastTypeValue; // Переменная состояния

	CSymbolsTable::CTable table; // таблица, которую мы строим
};

