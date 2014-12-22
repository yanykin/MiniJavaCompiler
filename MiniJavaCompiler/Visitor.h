/*
* ????????? ??????? ?????????????? "??????????"
*/
#pragma once
#include <iostream>
#include "NonTerminalSymbols.h"

class IVisitor {
public:
	virtual void Visit( const CProgram* node ) = 0;
	virtual void Visit( const CMainClassDeclaration* node ) = 0;
	virtual void Visit( const CClassDeclaration* node ) = 0;
	virtual void Visit( const CClassExtendsDeclaration* node ) = 0;
	virtual void Visit( const CClassDeclarationList* node ) = 0;
	virtual void Visit( const CVariableDeclaration* node ) = 0;
	virtual void Visit( const CVariableDeclarationList* node ) = 0;
	virtual void Visit( const CMethodDeclaration* node ) = 0;
	virtual void Visit( const CMethodDeclarationList* node ) = 0;
	virtual void Visit( const CFormalList* node ) = 0;
	virtual void Visit( const CFormalRestList* node ) = 0;
	virtual void Visit( const CBuiltInType* node ) = 0;
	virtual void Visit( const CUserType* node ) = 0;
	virtual void Visit( const CStatementList* node ) = 0;
	virtual void Visit( const CStatementBlock* node ) = 0;
	virtual void Visit( const CIfStatement* node ) = 0;
	virtual void Visit( const CWhileStatement* node ) = 0;
	virtual void Visit( const CPrintStatement* node ) = 0;
	virtual void Visit( const CAssignmentStatement* node ) = 0;
	virtual void Visit( const CArrayElementAssignmentStatement* node ) = 0;
	virtual void Visit( const CBinaryOperatorExpression* node ) = 0;
	virtual void Visit( const CIndexAccessExpression* node ) = 0;
	virtual void Visit( const CLengthExpression* node ) = 0;
	virtual void Visit( const CMethodCallExpression* node ) = 0;
	virtual void Visit( const CIntegerOrBooleanExpression* node ) = 0;
	virtual void Visit( const CIdentifierExpression* node ) = 0;
	virtual void Visit( const CThisExpression* node ) = 0;
	virtual void Visit( const CNewIntegerArrayExpression* node ) = 0;
	virtual void Visit( const CNewObjectExpression* node ) = 0;
	virtual void Visit( const CNegationExpression* node ) = 0;
	virtual void Visit( const CParenthesesExpression* node ) = 0;
	virtual void Visit( const CExpressionList* node ) = 0;
};