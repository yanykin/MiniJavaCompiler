/*
* Набор классов, необходимых для поддержки записей активации
*/

#pragma once
#include "Symbol.h"
#include "IRTree.h"
#include <map>

namespace Frame {
	class CFrame;
}


namespace Frame {

	// Интерфейс для переменной фрейма
	class IAccess {
	public:
		virtual ~IAccess() {}
		virtual const IRTree::IExp* GetExp( const Temp::CTemp* framePointer ) const = 0;
	};


	// CFrame ---------------------------------------------------------------------
	// Класс-контейнер с платформо-зависимой информацией о функции
	class CFrame {
	public:
		// Создать новый фрейм функции и указать количество передаваемых ему параметров
		CFrame( const Symbol::CSymbol* _name ) :
			name( _name ),
			formalCount( 0 ),
			framePointer( Temp::CTemp( Symbol::CSymbol::GetSymbol("FP") ) ),
			thisPointer( Temp::CTemp () ),
			returnPointer( Temp::CTemp( Symbol::CSymbol::GetSymbol( "RP" ) ) ),

			prologueLabel( Temp::CLabel() ),
			startLabel( Temp::CLabel() ),
			epilogueLabel( Temp::CLabel() )
		{
			const Temp::CTemp* eax = new Temp::CTemp( Symbol::CSymbol::GetSymbol( "EAX" ) );
			// const Temp::CTemp* ebx = new Temp::CTemp( Symbol::CSymbol::GetSymbol( "EBX" ) );
			const Temp::CTemp* ecx = new Temp::CTemp( Symbol::CSymbol::GetSymbol( "ECX" ) );
			const Temp::CTemp* edx = new Temp::CTemp( Symbol::CSymbol::GetSymbol( "EDX" ) );

			callDefArgs = new Temp::CTempList(
				eax, new Temp::CTempList(
					ecx, new Temp::CTempList( edx )
				)
			);
		};

		// Добавить аргумент функции
		void AddFormal( const Symbol::CSymbol* name );

		// Добавить локальную переменную
		void AddLocal( const Symbol::CSymbol* name );

		// Получить количество локальных переменных
		int GetFormalCount() const { return formalCount; }

		// Получить к переменной фрейма по имени (это может быть как аргумент функции, так и локальная переменная)
		const IAccess* FindLocalOrFormal( const Symbol::CSymbol* name ) const;

		// Возвращает размер машинного слова в байтах
		static int GetWordSize() { return wordSize; }

		const Temp::CTemp* FramePointer() const { return &framePointer; }
		const Temp::CTemp* ThisPointer() const { return &thisPointer; }
		const Temp::CTemp* ReturnPointer() const { return &returnPointer;  }

		// Получить имя метода
		const Symbol::CSymbol* GetMethodName() const { return name; }

		const Temp::CLabel* GetPrologueLanel() const { return &prologueLabel; }
		const Temp::CLabel* GetStartLabel() const { return &startLabel; }
		const Temp::CLabel* GetEpilogueLabel() const { return &epilogueLabel; }

		// Возвращает регистры, затираемые после вызова CALL
		const Temp::CTempList* callDefArgs;
		const Temp::CTempList* GetCallDefArgs() const {
			return callDefArgs;
		}

	private:
		static const int wordSize = 4; // Размер машинного слова для нашей платформы
		const Symbol::CSymbol* name; // Имя метода

		int formalCount; // количество переданных методу параметров
	
		std::map<const Symbol::CSymbol*, const IAccess*> localVariables; // Локальные переменные
		std::map<const Symbol::CSymbol*, const IAccess*> objectFields; // Поля объекта, метод которого мы вызываем
		std::map<const Symbol::CSymbol*, const IAccess*> methodFormals; // Аргументы метода, переданные при вызове

		// Стандартные регистры
		const Temp::CTemp framePointer;
		const Temp::CTemp thisPointer;
		const Temp::CTemp returnPointer; // куда фрейм будет записывать возвращаемое значение функции

		// Метки пролог, тело и эпилог функции
		Temp::CLabel prologueLabel;
		Temp::CLabel startLabel;
		Temp::CLabel epilogueLabel;
	};

	// Реализация интерфейса в случае расположения переменной во фрейме
	class CVariableInFrame : public IAccess {
	public:
		CVariableInFrame( int _offsetInWords ) :
			offsetInWords( _offsetInWords ) {};
		virtual const IRTree::IExp* GetExp( const Temp::CTemp* framePointer ) const {
			// TODO: реализовать
			return
				new IRTree::MEM(
				new IRTree::BINOP(
				IRTree::BO_PLUS,
				new IRTree::TEMP( framePointer ),
				new IRTree::CONST( offsetInWords * CFrame::GetWordSize() )
				)
				);
		}
	private:
		int offsetInWords; // смещение от начала стека
	};

	//...и в случае расположения в стеке
	class CVariableInRegister : public IAccess {
	public:
		CVariableInRegister( const Temp::CTemp* _registerLabel ) : registerLabel( _registerLabel ) {};
		virtual const IRTree::IExp* GetExp( const Temp::CTemp* framePointer ) const {
			return new IRTree::TEMP( registerLabel );
		}
	private:
		const Temp::CTemp* registerLabel; // временная переменная, характеризующая регистр
	};

} // namespace Frame