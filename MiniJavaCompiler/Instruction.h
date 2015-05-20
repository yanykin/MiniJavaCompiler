/* Набор классов, отвечающий за генерацию машинного кода */
#pragma once
#include <string>
#include <list>
#include <map>

#include "IRTree.h"
#include "Frame.h"

namespace CodeGeneration {
	
	// Абстрактный класс машинной инструкции
	class IInstruction {
	public:
		virtual ~IInstruction() {};
		std::string AsmCodeTemplate;
		virtual const Temp::CTempList* UsedVariables() const = 0;
		virtual const Temp::CTempList* DefinedVariables() const = 0;
		virtual const Temp::CLabelList* JumpTargets() const = 0;

		std::string Format( const std::map<Temp::CTemp*, std::string>& mapping) const;
	};

	class OPER : public IInstruction {
	public:
		OPER( const std::string& asmCode, Temp::CTempList* dst, Temp::CTempList* src, Temp::CLabelList* jumps ) :
			_usedVars( dst ), _definedVars( src ), _jumpTargets( jumps ) {
			AsmCodeTemplate = asmCode;
		};
		OPER( const std::string& asmCode, Temp::CTempList* dst, Temp::CTempList* src ) :
			_usedVars( dst ), _definedVars( src ), _jumpTargets( nullptr ) {
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


	private:
		const Temp::CTempList* _usedVars;
		const Temp::CTempList* _definedVars;
		const Temp::CLabelList* _jumpTargets;
	};

	class MOVE : public IInstruction {
	public:
		MOVE( const std::string& asmCode, Temp::CTemp* dst, Temp::CTemp* src ):
			_destination(dst), _source(src) {
			AsmCodeTemplate = asmCode;
		}
		const Temp::CTempList* UsedVariables() const {
			return new Temp::CTempList( _destination );
		}
		const Temp::CTempList* DefinedVariables() const {
			return new Temp::CTempList( _source );
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

	// Класс, отвечающий за генерацию машинного кода
	class CCodeGenerator {
	public:
		CCodeGenerator( const CStmList* statements, const Frame::CFrame* methodFrame ):
		_statements(statements), _methodFrame(methodFrame) {

		}
	private:
		const CStmList* _statements; // Выражения для данного фрейма
		const Frame::CFrame* _methodFrame; // Сам фрейм
		std::list<IInstruction*> _instructions; // сгенерируемые машинные инструкции

		CTypeHelper _helper;

		void emit( IInstruction* instruction ); // добавляем новую инструкцию

		// Генерирует инструкции для всего дерева
		std::list<IInstruction*> generateCode( IRTree::IStm* rootStatement );

		// Вспомогательные функции для быстрого создания списка
		Temp::CTempList*  L( Temp::CTemp* t1 ) { return new Temp::CTempList( t1 ); }
		Temp::CTempList*  L( Temp::CTemp* t1, Temp::CTemp* t2 ) { return new Temp::CTempList( t1, t2 ); }
		Temp::CTempList*  L( Temp::CTemp* t1, Temp::CTemp* t2, Temp::CTemp* t3 ) { return new Temp::CTempList( t1, t2, t3 ); }

		Temp::CLabelList* L( const Temp::CLabel* l1 ) { return new Temp::CLabelList( l1 ); }
		Temp::CLabelList* L( const Temp::CLabel* l1, const Temp::CLabel* l2 ) { return new Temp::CLabelList( l1, l2 ); }

		// Проходит узлы дерева и генерирует инструкции
		void munchStm( const IRTree::IStm* statement );
		void munchStm( const IRTree::MOVE* move );
		void munchStm( const IRTree::EXP* exp );
		void munchStm( const IRTree::JUMP* jump );
		void munchStm( const IRTree::CJUMP* cjump );
		void munchStm( const IRTree::SEQ* seq );
		void munchStm( const IRTree::LABEL* label );

		Temp::CTemp* munchExp( const IRTree::IExp* expression );
		Temp::CTemp* munchExp( const IRTree::CONST* constExp );
		Temp::CTemp* munchExp( const IRTree::NAME* name );
		const Temp::CTemp* munchExp( const IRTree::TEMP* temp );
		Temp::CTemp* munchExp( const IRTree::BINOP* binop );
		Temp::CTemp* munchExp( const IRTree::MEM* mem );
		Temp::CTemp* munchExp( const IRTree::CALL* call );

		// Обходит список аргументов вызываемой функции и строит список временных переменных, куда
		// они сохраняются
		Temp::CTempList* munchArgs(const IRTree::CExpList* expList);

		// Для каждой команды создаём отдельный метод и проверяем, накрывает ли тайл данный узел
		// IStm

		void munchSEQ( const IRTree::IStm* ); // s1; s2;
		void munchMOVE( const IRTree::IStm* ); // MOV [e1 + i], e2
	};
}