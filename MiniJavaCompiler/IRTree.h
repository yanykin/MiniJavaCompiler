/*
	namespace для узлов дерева промежуточного представления
*/
#pragma once
#include "Temp.h"
#include "IRTreeVisitor.h"

namespace IRTree
{
	class IStm
	{
	public:
		virtual ~IStm() {};
		virtual void Accept( IIRTreeVisitor *visitor ) const = 0;
	};
	class IExp
	{
	public:
		virtual ~IExp() {};
		virtual void Accept( IIRTreeVisitor *visitor ) const = 0;
	};

	// константы
	enum TBinop
	{
		// арифметика
		BO_PLUS,
		BO_MINUS,
		BO_MUL,
		BO_DIV,

		// булевы
		BO_AND,
		BO_OR,
		BO_LSHIFT,
		BO_RSHIFT,
		BO_ARSHIFT,
		BO_XOR
	};

	enum TCJump
	{
		// логические
		CJ_EQ, // equal
		CJ_NE, // not equal
		CJ_LT, // less than
		CJ_GT, // great than
		CJ_LE, // less or equal
		CJ_GE, // great or equal
		// TODO:
		CJ_ULT, // ?? ЧТО
		CJ_ULE, // ?? ЭТО
		CJ_UGT, // ?? ЗНАЧИТ
		CJ_UGE // ?? ????
	};

	// вспомогательный классы
	class CExpList
	{
	public:
		CExpList( const IExp* _head, const CExpList* _tail ) 
			: head( _head ), tail( _tail )
		{
		};
		const IExp* GetHead() const { return head; }
		const CExpList* GetTail() const { return tail; }
		void Accept( IIRTreeVisitor *visitor ) const { visitor->Visit( this ); };
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
		void Accept( IIRTreeVisitor *visitor ) const { visitor->Visit( this ); };
	private:
		const IStm* head;
		const CStmList* tail;
	};

	// классы растущие из IExp
	class CONST : public IExp {
	public:
		CONST( int _value )
			: value( _value )
		{
		};
		int GetValue() const { return value; }
		void Accept( IIRTreeVisitor *visitor ) const { visitor->Visit( this ); };
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
		void Accept( IIRTreeVisitor *visitor ) const { visitor->Visit( this ); };
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
		void Accept( IIRTreeVisitor *visitor ) const { visitor->Visit( this ); };
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
		void Accept( IIRTreeVisitor *visitor ) const { visitor->Visit( this ); };
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
		void Accept( IIRTreeVisitor *visitor ) const { visitor->Visit( this ); };
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
		void Accept( IIRTreeVisitor *visitor ) const { visitor->Visit( this ); };
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
		void Accept( IIRTreeVisitor *visitor ) const { visitor->Visit( this ); };
	private:
		const IStm* stm;
		const IExp* exp;
	};

	// классы растущие из IStm
	class MOVE : public IStm
	{
	public:
		MOVE( const IExp* _dst, const IExp* _src )
			: dst( _dst ), src( _src )
		{
		};
		const IExp* GetDst() const { return dst; }
		const IExp* GetSrc() const { return src; }
		void Accept( IIRTreeVisitor *visitor ) const { visitor->Visit( this ); };
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
		void Accept( IIRTreeVisitor *visitor ) const { visitor->Visit( this ); };
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
		JUMP( const Temp::CLabel* l )
			: exp( new NAME( l ) ), targets( new Temp::CLabelList( l, nullptr ) )
		{
		};
		const IExp* GetExp() const { return exp; }
		const Temp::CLabelList* GetTargets() const { return targets; }
		void Accept( IIRTreeVisitor *visitor ) const { visitor->Visit( this ); };
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
		void Accept( IIRTreeVisitor *visitor ) const { visitor->Visit( this ); };
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
		void Accept( IIRTreeVisitor *visitor ) const { visitor->Visit( this ); };
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
		void Accept( IIRTreeVisitor *visitor ) const { visitor->Visit( this ); };
	private:
		const Temp::CLabel* label;
	};
};

