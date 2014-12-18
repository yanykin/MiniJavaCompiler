/*
	namespace ??? ????? ?????? ?????????????? ?????????????
*/
#pragma once
#include "Temp.h"

namespace IRTree
{
	class IStm
	{
	public:
		virtual ~IStm() {};
	};
	class IExp
	{
	public:
		virtual ~IExp() {};
	};

	// ????????????
	enum TBinop
	{
		// ??????????
		BO_PLUS,
		BO_MINUS,
		BO_MUL,
		BO_DIV,

		// ???????
		BO_AND,
		BO_OR,	// ? ? ??? ???? ???? ??
		BO_LSHIFT,
		BO_RSHIFT,
		BO_ARSHIFT,
		BO_XOR
	};

	enum TCJump
	{
		// ??????????
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

	// ??????????????? ??????
	class CExpList
	{
	public:
		CExpList( const IExp* _head, const CExpList* _tail ) 
			: head( _head ), tail( _tail )
		{
		};
		const IExp* GetHead() const { return head; }
		const CExpList* GetTail() const { return tail; }
	private:
		const IExp* head;
		const CExpList* tail;
	};
	
	class CStmList
	{
	public:
		CStmList( const IStm* _head, const CStmList* _tail )
			: head( _head ), tail( _tail )
		{
		};
		const IStm* GetHead() const { return head; }
		const CStmList* GetTail() const { return tail; }
	private:
		const IStm* head;
		const CStmList* tail;
	};

	// ?????? ???????? ?? IExp
	class CONST : public IExp {
	public:
		CONST( int _value )
			: value( _value )
		{
		};
		int GetValue() const { return value; }
	private:
		int value;
	};

	class NAME : public IExp
	{
	public:
		NAME( const Temp::CLabel* _label )
			: label( _label )
		{
		};
		const Temp::CLabel* GetLabel() const { return label; }
	private:
		const Temp::CLabel* label;
	};

	class TEMP : public IExp
	{
	public:
		TEMP( const Temp::CTemp* _temp )
			: temp( _temp )
		{
		};
		const Temp::CTemp* GetTemp() const { return temp; }
	private:
		const Temp::CTemp* temp;
	};

	class BINOP : public IExp
	{
	public:
		BINOP( TBinop _binop, const IExp* _left, const IExp* _right )
			: binop( _binop ), left( _left ), right( _right )
		{
		};
		TBinop GetBinop() const { return binop; }
		const IExp* GetLeft() const { return left; }
		const IExp* GetRight() const { return right; }
	private:
		const TBinop binop;
		const IExp* left;
		const IExp* right;
	};

	class MEM : public IExp
	{
	public:
		MEM( const IExp* _exp )
			: exp( _exp )
		{
		};
		const IExp* GetExp() const { return exp; }
	private:
		const IExp* exp;
	};

	class CALL : public IExp
	{
	public:
		CALL( const IExp* _func, const CExpList* _args )
			: func( _func ), args( _args )
		{
		};
		const IExp* GetFunc() const { return func; }
		const CExpList* GetArgs() const { return args; }
	private:
		const IExp* func;
		const CExpList* args;
	};

	class ESEQ : public IExp
	{
	public:
		ESEQ( const IStm* _stm, const IExp* _exp )
			: stm( _stm ), exp( _exp )
		{
		};
		const IStm* GetStm() const { return stm; }
		const IExp* GetExp() const { return exp; }
	private:
		const IStm* stm;
		const IExp* exp;
	};

	// ?????? ???????? ?? IStm
	class MOVE : public IStm
	{
	public:
		MOVE( const IExp* _dst, const IExp* _src )
			: dst( _dst ), src( _src )
		{
		};
		const IExp* GetDst() const { return dst; }
		const IExp* GetSrc() const { return src; }
	private:
		const IExp* dst;
		const IExp* src;
	};

	class EXP : public IStm
	{
	public:
		EXP( const IExp* _exp )
			: exp( _exp )
		{
		};
		const IExp* GetExp() const { return exp; }
	private:
		const IExp* exp;
	};
	
	class JUMP : public IStm
	{
	public:
		JUMP( const IExp* _exp, const Temp::CLabelList* _targets )
			: exp( _exp ), targets( _targets )
		{
		};
		const IExp* GetExp() const { return exp; }
		const Temp::CLabelList* GetTargets() { return targets; }
	private:
		const IExp* exp;
		const Temp::CLabelList* targets;
	};

	class CJUMP : public IStm
	{
	public:
		CJUMP( TCJump _relop, const IExp* _left, const IExp* _right, const Temp::CLabel* _iftrue, const Temp::CLabel* _iffalse )
			: relop( _relop ), left( _left ), right( _right ), iftrue( _iftrue ), iffalse( _iffalse )
		{
		};
		TCJump GetRelop() const { return relop; }
		const IExp* GetLeft() const { return left; }
		const IExp* GetRight() const { return  right; }
		const Temp::CLabel* GetIfTrue() const { return iftrue; }
		const Temp::CLabel* GetIfFalse() const { return iffalse; }
	private:
		TCJump relop;
		const IExp* left;
		const IExp* right;
		const Temp::CLabel* iftrue;
		const Temp::CLabel* iffalse;
	};

	class SEQ : public IStm
	{
	public:
		SEQ( const IStm* _left, const IStm* _right )
			: left( _left ), right( _right )
		{
		};
		const IStm* GetLeft() const { return left; }
		const IStm* GetRight() const { return right; }
	private:
		const IStm* left;
		const IStm* right;
	};

	class LABEL : public IStm
	{
	public:
		LABEL( const Temp::CLabel* _label )
			: label( _label )
		{
		};
		const Temp::CLabel* GetLabel() const { return label; }
	private:
		const Temp::CLabel* label;
	};
};

