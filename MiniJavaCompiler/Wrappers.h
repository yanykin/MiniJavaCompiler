#pragma once
#include "IRTree.h"
#include "Temp.h"
#include <assert.h>

namespace Translate
{
	class ISubtreeWrapper
	{
	public:
		virtual ~ISubtreeWrapper() {}
		virtual const IRTree::IExp* ToExp() const = 0; // ��� Expr
		virtual const IRTree::IStm* ToStm() const = 0; // ��� Stm
		virtual const IRTree::IStm* ToConditional( const Temp::CLabel* t, const Temp::CLabel* f ) const = 0; // ��� if/jump
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
		const IRTree::IExp* ToExp() const { assert( false ); }
		const IRTree::IStm* ToStm() const { return stm; }
		const IRTree::IStm* ToConditional( const Temp::CLabel* t, const Temp::CLabel* f ) const { assert( false ); }
	private:
		const IRTree::IStm* stm;
	};

	class CConditionalWrapper : public ISubtreeWrapper
	{
	public:
		const IRTree::IExp* ToExp() const;
		const IRTree::IStm* ToStm() const;
		const IRTree::IStm* ToConditional( const Temp::CLabel* t, const Temp::CLabel* f ) const = 0;
	};

	class CRelativeCmpWrapper : public CConditionalWrapper
	{
	public:
		CRelativeCmpWrapper( IRTree::TCJump op, const IRTree::IExp* e1, const IRTree::IExp* e2 )
			: expr1( e1 ), expr2( e2 ), oper( op )
		{
		};
		virtual const IRTree::IStm* ToConditional( const Temp::CLabel* t, const Temp::CLabel* f ) const;
	private:
		const IRTree::IExp* expr1;
		const IRTree::IExp* expr2;
		IRTree::TCJump oper;
	};
}
