/* ����� �������, ���������� �� ��������� ��������� ���� */
#pragma once
#include <string>
#include <list>
#include <map>

#include "IRTree.h"
#include "Frame.h"

namespace CodeGeneration {
	
	// ����������� ����� �������� ����������
	class IInstruction {
	protected:
		static const char PLACEHOLDER = '`';
		std::string AsmCodeTemplate;

	public:
		virtual ~IInstruction() {};
		virtual const Temp::CTempList* UsedVariables() const = 0;
		virtual const Temp::CTempList* DefinedVariables() const = 0;
		virtual const Temp::CLabelList* JumpTargets() const = 0;

		std::string Format( Temp::ITempMap* mapping ) const {

			// ��������� �����������
			std::map<std::string, std::string> placeholderValues;
			std::string placeholderString( 1, PLACEHOLDER );

			int i = 0;
			const Temp::CTempList* list = nullptr;
			const Temp::CTemp* temp = nullptr;
			// ���������� ������������ ���������� (`s0, `s1 ... )
			i = 0;
			list = this->UsedVariables();
			while ( list ) {
				temp = list->GetHead();
				placeholderValues[ placeholderString + "s" + std::to_string( i ) ] = mapping->Map( temp );
				list = list->GetTail();
			}

			// ���������� ������������ ����������� (`d0, `d1 ... )
			i = 0;
			list = this->DefinedVariables();
			while ( list ) {
				temp = list->GetHead();
				placeholderValues[ placeholderString + "d" + std::to_string( i ) ] = mapping->Map( temp );
				list = list->GetTail();
			}
			// ���������� ����� (`j0, `j1 ... )
			i = 0;
			const Temp::CLabelList* labelList = this->JumpTargets();
			const Temp::CLabel* label = nullptr;
			while ( labelList ) {
				label = labelList->GetHead();
				placeholderValues[ placeholderString + "j" + std::to_string( i ) ] = label->Name();
				labelList = labelList->GetTail();
			}

			std::string command = AsmCodeTemplate;
			// ������ ������������ �������, ������� placeholders �� ��������
			for ( auto& item : placeholderValues ) {
				std::string placeholder = item.first;
				std::string value = item.second;

				// ������� ���������
				size_t placeholderPosition = command.find( placeholder );
				if ( placeholderPosition != std::string::npos ) {
					// ������ ������
					command.replace( placeholderPosition, placeholder.length(), value );
				}
			}

			// ���������� �������������� �������
			return command;
		}
	};

	// ��������� alias
	typedef std::list<IInstruction*> TInstructionsList;

	class OPER : public IInstruction {
	public:
		OPER( const std::string& asmCode, const Temp::CTempList* dst, const Temp::CTempList* src, const Temp::CLabelList* jumps ) :
			_usedVars( src ), _definedVars( dst ), _jumpTargets( jumps ) {
			AsmCodeTemplate = asmCode;
		};
		OPER( const std::string& asmCode, const Temp::CTempList* dst, const Temp::CTempList* src ) :
			_usedVars( src ), _definedVars( dst ), _jumpTargets( nullptr ) {
			AsmCodeTemplate = asmCode;
		};
		const Temp::CTempList* UsedVariables() const {
			return _usedVars;
		}
		const Temp::CTempList* DefinedVariables() const {
			return _definedVars;
		}
		const Temp::CLabelList* JumpTargets() const {
			return _jumpTargets;	
		}

		// ���������� ������� ������������ �������
		
		

	private:
		const Temp::CTempList* _usedVars;
		const Temp::CTempList* _definedVars;
		const Temp::CLabelList* _jumpTargets;

		
	};

	class MOVE : public IInstruction {
	public:
		MOVE( const std::string& asmCode, const Temp::CTemp* dst, const Temp::CTemp* src ) :
			_destination(dst), _source(src) {
			AsmCodeTemplate = asmCode;
		}
		const Temp::CTempList* UsedVariables() const {
			return new Temp::CTempList( _source );
		}
		const Temp::CTempList* DefinedVariables() const {
			return new Temp::CTempList( _destination );
		}
		const Temp::CLabelList* JumpTargets() const {
			return nullptr;
		}

	private:
		const Temp::CTemp* _destination;
		const Temp::CTemp* _source;
	};

	class LABEL : public IInstruction {
	public:
		LABEL( const std::string& asmCode, const Temp::CLabel* label ) :
			_label( label ) {
			AsmCodeTemplate = asmCode;
		};
		const Temp::CTempList* UsedVariables() const {
			return nullptr;
		}
		const Temp::CTempList* DefinedVariables() const {
			return nullptr;
		}
		const Temp::CLabelList* JumpTargets() const {
			return new Temp::CLabelList( _label );
		}
		
	private:
		const Temp::CLabel* _label;
	};

	// �����, ���������� �� ��������� ��������� ����
	class CCodeGenerator {
	public:
		CCodeGenerator( const IRTree::CStmList* statements, const Frame::CFrame* methodFrame ) :
		_statements(statements), _methodFrame(methodFrame) {

		}
		void Generate(); // ��������� ��������� ����
		TInstructionsList GetInstrucions() const; // ���������� ������ ��������������� ����������

	private:
		const IRTree::CStmList* _statements; // ��������� ��� ������� ������
		const Frame::CFrame* _methodFrame; // ��� �����
		TInstructionsList _instructions; // ������������� �������� ����������

		IRTree::CTypeHelper _helper;

		void emit( IInstruction* instruction ); // ��������� ����� ����������

		// ���������� ���������� ��� ����� ������
		std::list<IInstruction*> generateCode( const IRTree::IStm* rootStatement );

		// ��������������� ������� ��� �������� �������� ������
		Temp::CTempList*  L( const Temp::CTemp* t1 ) { return new Temp::CTempList( t1 ); }
		Temp::CTempList*  L( const Temp::CTemp* t1, const Temp::CTemp* t2 ) { return new Temp::CTempList( t1, t2 ); }
		Temp::CTempList*  L( const Temp::CTemp* t1, const Temp::CTemp* t2, const Temp::CTemp* t3 ) { return new Temp::CTempList( t1, t2, t3 ); }

		Temp::CLabelList* L( const Temp::CLabel* l1 ) { return new Temp::CLabelList( l1 ); }
		Temp::CLabelList* L( const Temp::CLabel* l1, const Temp::CLabel* l2 ) { return new Temp::CLabelList( l1, l2 ); }

		// �������� ���� ������ � ���������� ����������
		void munchStm( const IRTree::IStm* statement );
		void munchStm( const IRTree::MOVE* move );
		void munchStm( const IRTree::EXP* exp );
		void munchStm( const IRTree::JUMP* jump );
		void munchStm( const IRTree::CJUMP* cjump );
		void munchStm( const IRTree::SEQ* seq );
		void munchStm( const IRTree::LABEL* label );

		const Temp::CTemp* munchExp( const IRTree::IExp* expression );
		const Temp::CTemp* munchExp( const IRTree::CONST* constExp );
		const Temp::CTemp* munchExp( const IRTree::NAME* name );
		const Temp::CTemp* munchExp( const IRTree::TEMP* temp );
		const Temp::CTemp* munchExp( const IRTree::BINOP* binop );
		const Temp::CTemp* munchExp( const IRTree::MEM* mem );
		const Temp::CTemp* munchExp( const IRTree::CALL* call );

		// ������������ ����� ������� � ��������� � ���������� true, ���� ������� ��� �������
		bool munchFunctionCall( const IRTree::MOVE* move );
		bool munchProcedureCall( const IRTree::EXP* exp );

		// ������� ������ ���������� ���������� ������� � ������ ������ ��������� ����������, ����
		// ��� �����������
		const Temp::CTempList* munchArgs( const IRTree::CExpList* expList );

		// ��� ������ ������� ������ ��������� ����� � ���������, ��������� �� ���� ������ ����
		// IStm

		void munchSEQ( const IRTree::IStm* ); // s1; s2;
		void munchMOVE( const IRTree::IStm* ); // MOV [e1 + i], e2
	};
}