#pragma once
#include "IRTree.h"
#include "Temp.h"
#include "Frame.h"


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

	// Приведение кода к линейному виду
	class CCanon {
	public:
		static const CStmList* Linearize( const IStm* statement );
	};
	
	// Вспомогательная структура базового блока
	struct CBasicBlock {
		CBasicBlock(): Label(nullptr), Jump(nullptr) {};
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

	// Разбиение на базовые блоки
	class CStatementsSplitter {
	public:
		CStatementsSplitter( const Frame::CFrame* method, const CStmList* statements );
		std::vector<CStmList*> Blocks; // Сами базовые блоки

	private:
		void split( const CStmList* statements ); // Разбиение на блоки
		CBasicBlock buffer; // аккумулятор выражений для блока
		std::vector<CBasicBlock> foundBlocks; // найденные блоки

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

		// Соединяем блоки между собой, добавляя отсутствующие инструкии LABEL и JUMP
		void connectBlocks(const Frame::CFrame* methodFrame);

	};

	// Выстраивание блоков в односторонний порядок
	class CTraceSchedule {
	public:
		CTraceSchedule( std::vector<CBasicBlock>& basicBlocks );
		const CStmList* Statements;

		const CStmList* GetReorderedStatements() {
			return Statements;
		}

	private:
		std::map<const Temp::CLabel*, CBasicBlock*> labelToBlock; // отображение меток в блоки
		std::vector<CBasicBlock*> reorderedBlocks; // тот же список блоков, но уже переупорядоченных

		// Обходит блоки по меткам
		void generateTraces(std::vector<CBasicBlock>& basicBlocks);

		// Оптимизирует блоки по CJUMP'ам, чтобы блок за false-меткой шёл сразу
		void optimizeCJUMPBlocks();

		// Переводит базовые блоки в набор инструкций
		void translateToStatements();
	};


}