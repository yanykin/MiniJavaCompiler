/*
* ��������� ��� ������� � ��������� ������� ��������, ���������������� ��� ������� ���� ����� ����������
* ��������������� ������
*/
#pragma once
#include <string>
#include <unordered_map>

namespace Symbol {

	// ��������� ������, �� ������� ������������ ������ 
	class CSymbol {
	public:
		// ���������� ������ �� �������� ������
		static CSymbol* GetSymbol( const std::string& key ) {
			auto result = mapping.find( key );
			if ( result == mapping.end() ) {
				CSymbol *symbol = new CSymbol( key );
				mapping[ key ] = symbol;
				return symbol;
			} else {
				return result->second;
			}
		}

		// ���������� ������ ��� �������� �������
		const std::string& GetString() const { return string_key; };
	private:
		// ��������� �����������
		CSymbol( const std::string& s ) : string_key( s ) {};

		// ������, �� ������� ��������� ������
		const std::string string_key;

		// ������� ��� �����
		static std::unordered_map<std::string, CSymbol*> mapping;
		
	};

	// ����� ��������� ��������
	template<class TObject>
	class CStorage {
	public:
		// ������ ��������� ��������, ��� ������� ������ CSymbol, � ���������� - ������� ���� TObject
		CStorage<TObject>() {};
		// ��������� ������ �� ���������� �����
		void InsertObject( CSymbol* symbol, TObject value ) {
			table[ symbol ] = value;
		};
		// ���������� ��������� �� ������
		TObject GetObject( CSymbol* symbol ) const {
			auto result = table.find( symbol );
			return result != table.end() ? result->second : NULL;
		};

	private:
		std::unordered_map<CSymbol*, TObject> table;
	};
}