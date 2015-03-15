#pragma once
#include "IRTree.h"
#include "Temp.h"


using namespace IRTree;


class MoveCall: public IStm
{
public:
	MoveCall( const TEMP* d, const CALL* s ) : dst(d), src(s) {};

	const CExpList* kids() { return src->GetArgs(); }

	void Accept( IIRTreeVisitor *visitor ) const {}; // пока пустой
	//IStm build( CExpList kids ) { return new MOVE( dst, src.build( kids ) ); }
private:
	const TEMP* dst;
	const CALL* src;
};

class ExpCall: public IStm
{
public:
	ExpCall( const CALL* c ) : call( c ) {};

	// что есть дети Stm?? уже в дереве или где?
	//const CExpList* kids() { return call->kids; }

	void Accept( IIRTreeVisitor *visitor ) const {}; // пока пустой
	//public IStm build( Tree.ExpList kids ) { return new Tree.EXP( call.build( kids ) );}
private:
	const CALL* call;
};

class StmExpList
{
public:
	StmExpList( const IStm* s, const CExpList* e ) : stm( s ), exps( e ) {};

	const IStm* GetStm() const { return stm; }
	const CExpList* GetExps() const { return exps; }

private:
	const IStm* stm;
	const CExpList* exps;
};


namespace Canon
{
	bool isNop( const IStm* a );
	bool commute( const IStm* a, const IExp* b );
	const IStm* seq( const IStm* a, const IStm* b );

	const IStm* do_stm( const SEQ* s );
	const IStm* do_stm( const MOVE* s );
	const IStm* do_stm( const EXP* s );
	const IStm* do_stm( const IStm* s );

	const ESEQ* do_exp( const ESEQ* e );
	const ESEQ* do_exp( const IExp* e );

	const StmExpList* reorder( const CExpList* exps );
	const IStm* reorder_stm( const IStm* s );
	const ESEQ* reorder_exp( const IExp* e );

	const CStmList* linear( const SEQ* s, const CStmList* l );
	const CStmList* linear( const IStm* s, const CStmList* l );
	const CStmList* linearize( const IStm* s );
}