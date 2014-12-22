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
		const IRTree::IExp* ToExp() const { assert( false ); }
		const IRTree::IStm* ToStm() const { return stm; }
		const IRTree::IStm* ToConditional( const Temp::CLabel* t, const Temp::CLabel* f ) const { assert( false ); }
	private:
		const IRTree::IStm* stm;
	};
}