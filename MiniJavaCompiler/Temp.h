/*
	namespace Temp
*/
#pragma once
#include <string>
#include "Symbol.h"

namespace Temp
{
	// Метка - точка перехода в коде
	class CLabel
	{
	public:
		// Создать метку с уникальным именем
		CLabel();
		// Создать метку с заданным именем
		explicit CLabel( const Symbol::CSymbol* symbol );

		const std::string& Name() const { return name; }

	private:
		// Счётчик для создания уникальных идентификаторов
		static int nextUniqueId;
		std::string name;

		// Суффикс, добавляемый для поддержки уникальности
		static const std::string suffix;
		static const std::string separator;

	};

	// Временная переменная
	class CTemp
	{
	public:
		// Новая переменная с уникальным именем
		CTemp();
		// Новая переменная с заданным именем
		explicit CTemp( const Symbol::CSymbol* symbol );

		const std::string& Name() const { return name; }

	private:
		// Счётчик для создания уникальных имён
		static int nextUniqueId;
		std::string name;

		// Суффикс, добавляемый для поддержки уникальности
		static const std::string suffix;
		static const std::string separator;
	};
	// Список временных переменных
	class CTempList
	{
	public:
		CTempList( const CTemp* head, const CTempList* tail ) : _head( head ), _tail( tail ) {};
		// Вспомогательные конструкторы
		CTempList( const CTemp* head ) : _head( head ), _tail( nullptr ) {};
		CTempList( const CTemp* t1, const CTemp* t2 ) {
			_head = t1;
			_tail = new CTempList( t2 );
		}
		CTempList( const CTemp* t1, const CTemp* t2, const CTemp* t3 ) {
			_head = t1;
			_tail = new CTempList( t2, t3 );
		}
		const CTemp* GetHead() const { return _head; }
		const CTempList* GetTail() const { return _tail; }
	private:
		const CTemp* _head;
		const CTempList* _tail;
	};

	// Отображение "метка" -> "текстовое отображение"
	class ITempMap {
	public:
		virtual std::string Map(const CTemp* temp) = 0;
		virtual ~ITempMap() {};
	};
	class CDefaultTempMap : public ITempMap {
		std::string Map( const CTemp* temp ) {
			if ( temp ) {
				return temp->Name();
			}
			else {
				return "TEMP_NOT_FOUND";
			}
		}
	};

	// Лист меток
	class CLabelList
	{
	public:
		CLabelList( const CLabel* _head, const CLabelList* _tail )
			: head( _head ), tail( _tail )
		{};
		// Вспомогательные конструкторы
		CLabelList( const CLabel* _head ): head( _head ), tail( nullptr ) {};
		CLabelList( const CLabel* l1, const CLabel* l2 ) {
			head = l1;
			tail = new CLabelList( l2 );
		}
		const CLabel* GetHead() const { return head; }
		const CLabelList* GetTail() const { return tail; }
	private:
		const CLabel* head;
		const CLabelList* tail;
	};
};