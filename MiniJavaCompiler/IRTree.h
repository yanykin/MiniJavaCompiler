/*
	namespace для узлов дерева промежуточного представления
*/
#pragma once
#include "Temp.h"

namespace IRTree
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
		CExpList( const IExp* head, const CExpList* tail );
	};
	
	class CStmList
	{
	public:
		CStmList( const IStm* head, const CStmList* tail );
	};

	// классы растущие из IExp
	class CONST : public IExp {
	public:
		CONST( int value );
	};

	class NAME : public IExp
	{
	public:
		NAME( const Temp::CLabel* label );
	};

	class TEMP : public IExp
	{
	public:
		TEMP( const Temp::CTemp* temp );
	};

	class BINOP : public IExp
	{
	public:
		BINOP( const TBinop binop, const IExp* left, const IExp* right );
	};

	class MEM : public IExp
	{
	public:
		MEM( const IExp* exp );
	};

	class CALL : public IExp
	{
	public:
		CALL( const IExp* func, const CExpList* args );
	};

	class ESEQ : public IExp
	{
	public:
		ESEQ( const IStm* stm, const IExp* exp );
	};

	// классы растущие из IStm
	class MOVE : public IStm
	{
	public:
		MOVE( const IExp* dst, const IExp* src );
	};

	class EXP : public IStm
	{
	public:
		EXP( const IExp* exp );
	};
	
	class JUMP : public IStm
	{
	public:
		JUMP( const IExp* exp, const Temp::CLabelList* targets );
	};

	class CJUMP : public IStm
	{
	public:
		CJUMP( TCJump relop, const IExp* left, const IExp* right, const Temp::CLabel* iftrue, const Temp::CLabel* iffalse );
	};

	class SEQ : public IStm
	{
	public:
		SEQ( const IStm* left, const IStm* right );
	};

	class LABEL : public IStm
	{
	public:
		LABEL( const Temp::CLabel* label );
	};
};

