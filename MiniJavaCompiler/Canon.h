#pragma once
#include "IRTree.h"
#include "Temp.h"
#include "Frame.h"


using namespace IRTree;


class MoveCall: public IStm
{
public:
	MoveCall( const TEMP* d, const CALL* s ) : dst(d), src(s) {};

	virtual const CExpList* kids() const { return src->kids(); }

	virtual void Accept( IIRTreeVisitor *visitor ) const {}; // пока пустой
	virtual const IStm* build( const CExpList* kids ) const { return new MOVE( dst, src->build( kids ) ); }
private:
	const TEMP* dst;
	const CALL* src;
};

class ExpCall: public IStm
{
public:
	ExpCall( const CALL* c ) : call( c ) {};

	virtual const CExpList* kids() const { return call->kids(); }

	virtual void Accept( IIRTreeVisitor *visitor ) const {}; // пока пустой
	virtual const IStm* build( const CExpList* kids ) const { return new EXP( call->build( kids ) ); }
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

	// Вспомогательная структура базового блока
	struct CBasicBlock {
		CBasicBlock() : Label( nullptr ), Jump( nullptr ) {};
		const LABEL* Label; // метка 
		std::vector < const IStm* > FlowStatements; // выражения потока выполнения данного блока
		const IStm* Jump; // (без-)условный прыжок на следующий блок

		// Строит новый список выражений
		const CStmList* ConvertToStmList() {
			return nullptr;
		}

		void Clear() {
			Label = nullptr;
			Jump = nullptr;
			FlowStatements.clear();
		}

		void AddStatement( const IStm* statement ) {
			FlowStatements.push_back( statement );
		}

		const IRTree::JUMP* GetJUMP() const { return dynamic_cast< const IRTree::JUMP* >( Jump ); }
		const IRTree::CJUMP* GetCJUMP() const { return dynamic_cast< const IRTree::CJUMP* >( Jump ); }
	};

	// Приведение кода к линейному виду
	class CCanon {
	public:
		CCanon( const IStm* statement, const Frame::CFrame* frame );
		void Canonize(); // совершает все необходимые операции упрощения
		const CStmList* GetCanonizedStatements() const {
			return _canonizedStatementsList;
		}

	private:
		const IStm* _statement;				// корень IR-дерева, которое мы упрощаем
		const Frame::CFrame* _methodFrame;	// фрейм метода, с которым мы работаем
		const CStmList* _linearizedStatements; // упорядоченная структура дерева

		std::vector<CBasicBlock> _basicBlocks; // базовые блоки, на которые разбит метод
		const CStmList* _canonizedStatementsList; // список уже переупорядоченных инструкций

		void linearizeStatetment();				// Упорядочивает инструкии в линию
		void split();					// Делит последовательность инструкции на базовые блоки
		void connect();					// Соединяет блоки между собой, используя недостающие переходы
		void generateTraces();			// Генерирует покрытия и тем самым переупорядочивает блоки
		void optimizeCJUMPBlocks();		// Оптимизирует условные переходы
		void translateToStatements();	// Переводит в конечное дерево

		// Проверяет тип выражения
		static bool isLABEL( const IStm* statement ) {
			return dynamic_cast< const IRTree::LABEL* >( statement ) != nullptr;
		}
		static bool isJUMP( const IStm* statement ) {
			return dynamic_cast< const IRTree::JUMP* >( statement ) != nullptr;
		};
		static bool isCJUMP( const IStm* statement ) {
			return dynamic_cast< const IRTree::CJUMP* >( statement ) != nullptr;
		};
	};
	
	
}