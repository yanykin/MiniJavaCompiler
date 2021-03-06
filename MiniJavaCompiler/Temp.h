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

        bool operator ==( const CLabel& other ) const {
            return name == other.name;
        }

        bool operator != ( const CLabel& other ) const {
            return !( this->operator== ( other ) );
        }

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

        bool operator ==( const CTemp& other ) const {
            return name == other.name;
        }

        bool operator != ( const CTemp& other ) const {
            return !( this->operator== ( other ) );
        }

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
		const CTemp* GetHead() const { return _head; }
		const CTempList* GetTail() const { return _tail; }
	private:
		const CTemp* _head;
		const CTempList* _tail;
	};

	// ����������� "�����" -> "��������� �����������"
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

namespace std
{

	template<>
	struct hash < Temp::CTemp >
	{
		size_t operator()( const Temp::CTemp& val ) const
		{
			return hash<string>()( val.Name() );
		}
	};

	template<>
	struct hash < Temp::CLabel >
	{
		size_t operator()( const Temp::CLabel& val ) const
		{
			return hash<string>()( val.Name() );
		}
	};
}