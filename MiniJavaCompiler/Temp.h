/*
	namespace ??? ????? ? ???????? ??????????
*/
#pragma once
#include <string>

namespace Temp
{
	// ????? - ????? ???????? ? ????
	class CLabel
	{
	public:
		// ??????? ????? ? ?????????? ??????
		CLabel();
		// ??????? ????? ? ???????? ??????
		explicit CLabel( const std::string& symbol );
		const std::string& Name() const { return name; }

	private:
		// ??????? ??? ???????? ?????????? ???????????????
		static int nextUniqueId;
		std::string name;
	};

	// ????????? ??????????
	class CTemp
	{
	public:
		// ????? ?????????? ? ?????????? ??????
		CTemp();
		// ????? ?????????? ? ???????? ??????
		explicit CTemp( const std::string& symbol );
		~CTemp();
		const std::string& Name() const { return name; }

	private:
		// ??????? ??? ???????? ?????????? ????
		static int nextUniqueId;
		std::string name;
	};

	// ???? ?????
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

