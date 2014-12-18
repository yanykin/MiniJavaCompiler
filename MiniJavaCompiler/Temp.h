/*
	namespace для меток и времнных переменных
*/
#pragma once
#include <string>

namespace Temp
{
	// Метка - точка перехода в коде
	class CLabel
	{
	public:
		// Создать метку с уникальным именем
		CLabel();
		// Создать метку с заданным именем
		explicit CLabel( const std::string& symbol );
		const std::string& Name() const { return name; }

	private:
		// Счётчик для создания уникальных идентификаторов
		static int nextUniqueId;
		std::string name;
	};

	// Временная переменная
	class CTemp
	{
	public:
		// Новая переменная с уникальным именем
		CTemp();
		// Новая переменная с заданным именем
		explicit CTemp( const std::string& symbol );
		~CTemp();

		const std::string& Name() const { return name; }

	private:
		// Счётчик для создания уникальных имён
		static int nextUniqueId;
		std::string name;
	};

	// Лист меток
	class CLabelList
	{
	public:
		CLabelList( const CLabel* _head, const CLabelList* _tail )
			: head( _head ), tail( _tail )
		{
		};
		const CLabel* GetHead() const { return head; }
		const CLabelList* GetTail() const { return tail; }
	private:
		const CLabel* head;
		const CLabelList* tail;
	};
};

