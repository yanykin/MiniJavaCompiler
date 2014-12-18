/*
	namespace для узлов дерева промежуточного представления
*/
#pragma once
#include "Temp.h"

namespace lRTree
{
	class IStm {};
	class IExp {};

	// перечисления
	enum TBinop
	{
		// арифметика
		BO_PLUS,
		BO_MINUS,
		BO_MUL,
		BO_DIV,

		// булевые
		BO_AND,
		BO_OR,	// а у нас есть или? оО
		BO_LSHIFT,
		BO_RSHIFT,
		BO_ARSHIFT,
		BO_XOR
	};

	enum TCJump
	{
		// логические
		CJ_EQ,
		CJ_NE,
		CJ_LT,
		CJ_GT,
		CJ_LE,
		CJ_GE,
		CJ_ULT,
		CJ_ULE,
		CJ_UGT,
		CJ_UGE
	};

	// вспомогательный классы
	class CExpList
	{
	public:
		CExpList( IExp head, CExpList tail );
	};
	
	class CStmList
	{
	public:
		CStmList( IStm head, CStmList tail );
	};

	// классы растущие из IExp
	class CONST : public IExp {
	public:
		CONST( int value );
	};

	class NAME : public IExp
	{
	public:
		NAME( Temp::CLabel label );
	};

	class TEMP : public IExp
	{
	public:
		TEMP( Temp::CTemp temp );
	};

	class BINOP : public IExp
	{
	public:
		BINOP( TBinop binop, IExp left, IExp right );
		
	};

	class MEM : public IExp
	{
	public:
		MEM( IExp exp );
	};

	class CALL : public IExp
	{
	public:
		CALL( IExp func, CExpList args );
	};

	class ESEQ : public IExp
	{
	public:
		ESEQ( IStm stm, IExp exp );
	};

	// классы растущие из IStm
	class MOVE : public IStm
	{
	public:
		MOVE( IExp dst, IExp src );
	};

	class EXP : public IStm
	{
	public:
		EXP( IExp exp );
	};
	
	class JUMP : public IStm
	{
	public:
		JUMP( IExp exp, Temp::CLabelList targets );
	};

	class CJUMP : public IStm
	{
	public:
		CJUMP( TCJump relop, IExp left, IExp right, Temp::CLabel iftrue, Temp::CLabel iffalse );
	};

	class SEQ : public IStm
	{
	public:
		SEQ( IStm left, IStm right );
	};

	class LABEL : public IStm
	{
	public:
		LABEL( Temp::CLabel label );
	};
};

