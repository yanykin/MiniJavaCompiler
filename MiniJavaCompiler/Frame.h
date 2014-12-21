/*
* Набор классов, необходимых для поддержки записей активации
*/

#pragma once
#include "Symbol.h"

namespace Frame {

	// Переменная фрейма
	class IAccess {
	public:
		virtual ~IAccess() {}
		virtual const IRTree::IExp* GetExp( const IRTree::IExp* framePointer ) const = 0;
	};

	// CFrame ---------------------------------------------------------------------
	// Класс-контейнер с платформо-зависимой информацией о функции
	class CFrame {
	public:
		// Создать новый фрейм функции и указать количество передаваемых ему параметров
		CFrame( const Symbol::CSymbol* name );

		// Доступ к формальным параметрам и локальным переменным
		void AddFormal( const Symbol::CSymbol* name );
		void AddLocal( const Symbol::CSymbol* name );
		const IAccess* FindLocalOrFormal( const Symbol::CSymbol* name ) const;
		int WordSize() const { return wordSize; }
		const Temp::CTemp* FramePointer() const { return &fp; }
		const Temp::CTemp* ThisPointer() const { return &thisPtr; }

	private:
		// Размер машинного слова для нашей платформы
		static const int wordSize = 4;
		const Symbol::CSymbol* name; // имя метода
		std::map<const Symbol::CSymbol*, const IAccess*> locals; 

		// Стандартные регистры
		const Temp::CTemp fp;
		const Temp::CTemp thisPtr;

	};

} // namespace Frame