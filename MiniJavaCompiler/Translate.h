#pragma once
#include "IRTree.h"
#include "Temp.h"
#include "Visitor.h"
#include <assert.h>

namespace Translate
{
	class ISubtreeWrapper
	{
	public:
		virtual ~ISubtreeWrapper() {}
		virtual const IRTree::IExp* ToExp() const = 0; // как Expr
		virtual const IRTree::IStm* ToStm() const = 0; // как Stm
		virtual const IRTree::IStm* ToConditional( const Temp::CLabel* t, const Temp::CLabel* f ) const = 0; // как if/jump
	};

	class CExpConverter : public ISubtreeWrapper
	{
	public:
		CExpConverter( const IRTree::IExp* e ) : expr( e ) {}
		const IRTree::IExp* ToExp() const { return expr; }
		const IRTree::IStm* ToStm() const { return new IRTree::EXP( expr ); }
		const IRTree::IStm* ToConditional( const Temp::CLabel* t, const Temp::CLabel* f ) const;
	private:
		const IRTree::IExp* expr;
	};

	class CStmConverter : public ISubtreeWrapper
	{
	public:
		CStmConverter( const IRTree::IStm* e ) : stm( e ) {}
		const IRTree::IExp* ToExp() const { assert(false); }
		const IRTree::IStm* ToStm() const { return stm; }
		const IRTree::IStm* ToConditional( const Temp::CLabel* t, const Temp::CLabel* f ) const { assert( false ); }
	private:
		const IRTree::IStm* stm;
	};
}

class CTranslate : public IVisitor
{
public:
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
};