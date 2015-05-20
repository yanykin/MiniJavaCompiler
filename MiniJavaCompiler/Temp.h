/*
	namespace Temp
*/
#pragma once
#include <string>
#include "Symbol.h"

namespace Temp
{
	// ����� - ����� �������� � ����
	class CLabel
	{
	public:
		// ������� ����� � ���������� ������
		CLabel();
		// ������� ����� � �������� ������
		explicit CLabel( const Symbol::CSymbol* symbol );

		const std::string& Name() const { return name; }

	private:
		// ������� ��� �������� ���������� ���������������
		static int nextUniqueId;
		std::string name;

		// �������, ����������� ��� ��������� ������������
		static const std::string suffix;
		static const std::string separator;

	};

	// ��������� ����������
	class CTemp
	{
	public:
		// ����� ���������� � ���������� ������
		CTemp();
		// ����� ���������� � �������� ������
		explicit CTemp( const Symbol::CSymbol* symbol );

		const std::string& Name() const { return name; }

	private:
		// ������� ��� �������� ���������� ���
		static int nextUniqueId;
		std::string name;

		// �������, ����������� ��� ��������� ������������
		static const std::string suffix;
		static const std::string separator;
	};
	// ������ ��������� ����������
	class CTempList
	{
	public:
		CTempList( const CTemp* head, const CTempList* tail ) : _head( head ), _tail( tail ) {};
		// ��������������� ������������
		CTempList( const CTemp* head ) : _head( head ), _tail( nullptr ) {};
		CTempList( const CTemp* t1, const CTemp* t2 ) {
			_head = t1;
			_tail = new CTempList( t2 );
		}
		CTempList( const CTemp* t1, const CTemp* t2, const CTemp* t3 ) {
			_head = t1;
			_tail = new CTempList( t2, t3 );
		}
	private:
		const CTemp* _head;
		const CTempList* _tail;
	};

	// ���� �����
	class CLabelList
	{
	public:
		CLabelList( const CLabel* _head, const CLabelList* _tail )
			: head( _head ), tail( _tail )
		{};
		// ��������������� ������������
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