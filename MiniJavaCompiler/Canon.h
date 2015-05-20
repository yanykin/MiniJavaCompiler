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

	void Accept( IIRTreeVisitor *visitor ) const {}; // ���� ������
	const IStm* build( const CExpList* kids ) { return new MOVE( dst, src->build( kids ) ); }
private:
	const TEMP* dst;
	const CALL* src;
};

class ExpCall: public IStm
{
public:
	ExpCall( const CALL* c ) : call( c ) {};

	const CExpList* kids() { return call->kids(); }

	void Accept( IIRTreeVisitor *visitor ) const {}; // ���� ������
	const IStm* build( const CExpList* kids ) { return new EXP( call->build( kids ) ); }
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

	// ���������� ���� � ��������� ����
	class CCanon {
	public:
		CCanon( const IStm* statement, const Frame::CFrame* frame );
		void Canonize(); // ��������� ��� ����������� �������� ���������
		const CStmList* GetCanonizedStatements() const {
			return _canonizedStatementsList;
		}

	private:
		const IStm* _statement;				// ������ IR-������, ������� �� ��������
		const Frame::CFrame* _methodFrame;	// ����� ������, � ������� �� ��������
		const CStmList* _linearizedStatements; // ������������� ��������� ������

		std::vector<CBasicBlock> _basicBlocks; // ������� �����, �� ������� ������ �����
		const CStmList* _canonizedStatementsList; // ������ ��� ����������������� ����������

		void linearizeStatetment();				// ������������� ��������� � �����
		void split();					// ����� ������������������ ���������� �� ������� �����
		void connect();					// ��������� ����� ����� �����, ��������� ����������� ��������
		void generateTraces();			// ���������� �������� � ��� ����� ����������������� �����
		void optimizeCJUMPBlocks();		// ������������ �������� ��������
		void translateToStatements();	// ��������� � �������� ������

		// ��������� ��� ���������
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
	
	// ��������������� ��������� �������� �����
	struct CBasicBlock {
		CBasicBlock(): Label(nullptr), Jump(nullptr) {};
		const LABEL* Label; // ����� 
		std::vector < const IStm* > FlowStatements; // ��������� ������ ���������� ������� �����
		const IStm* Jump; // (���-)�������� ������ �� ��������� ����

		// ������ ����� ������ ���������
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
}