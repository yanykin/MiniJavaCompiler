/*
* �������� �������, ����������� ��� ��������� ������� ��������
*/
#pragma once
#include <string>
#include <list>
#include <map>

#include "Symbol.h"

// ������� �������� ��� ����� MiniJava
namespace CSymbolsTable {

	// ���������������
	class CClassInformation;
	class CMethodInformation;
	class CVariableInformation;

	// ������ ��������� �������
	class CTable {
	public:
		CTable() : declaredClasses() {};

		// ��������� ����� � ������� �������� � ���������� ���� ������/��������
		bool AddClass( CClassInformation *classInfo );

		// ���������� ������ �� ��������� � ����������� ������ ��� null, ���� ����� ����� �� �����
		CClassInformation* GetClassByName( const std::string& className );

	private:
		Symbol::CStorage < CClassInformation* > declaredClasses; // ����������� � ��������� ������
	};

	// ���������� � ���������� ������
	class CClassInformation {
	public:
		CClassInformation( std::string _name ) : name( Symbol::CSymbol::GetSymbol( _name ) ), isDerived( false ) {};
		CClassInformation( std::string _name, std::string _baseClassName ) :
			name( Symbol::CSymbol::GetSymbol( _name ) ),
			baseClassName( Symbol::CSymbol::GetSymbol( _baseClassName ) ),
			isDerived( true ) {};
		std::string GetName() const { return name->GetString(); };

		bool AddMethod( CMethodInformation* methodInfo );
		bool AddField( CVariableInformation* fieldInfo );

		// ���������� ������ �� ��������� � ����������� ������ ������ ��� null � ��������� ������
		CMethodInformation* GetMethodByName( std::string& methodName );
		// ���������� ��� ������ ��� ��������� ����������
		Symbol::CSymbol* GetFieldType( std::string& fieldName );

	private:
		Symbol::CSymbol* name; // ��� ������
		Symbol::CSymbol* baseClassName; // ������� �����, ���� ������������

		bool isDerived; // ����������� �� ���� ����� �� ������-�� ������� ������

		Symbol::CStorage < CVariableInformation* > fields; // ���� ������
		Symbol::CStorage < CMethodInformation* > methods; // ������ ������
	};

	// ���������� � ������ ������
	class CMethodInformation {
	public:
		CMethodInformation( std::string _name ) : name( Symbol::CSymbol::GetSymbol( _name ) ) {};
		std::string GetName() const { return name->GetString(); };

		void SetReturnType( Symbol::CSymbol* _returnType ) { returnType = _returnType; }
		Symbol::CSymbol* GetReturnType() const { return returnType; };

		bool AddParameter( CVariableInformation* param );
		bool AddLocalVariable( CVariableInformation* variable );

		// ���������� ���������� � ���� ���������, null, ���� ������ ��������� ���
		Symbol::CSymbol* GetArgumentType( const std::string& argumentName );

		// TODO: �������� ���������� ����� ���������/����������
		
		// ���������� � ��� ��������� ���������� ������
		Symbol::CSymbol* GetLocalVariableType( const std::string& variableName );

	private:
		Symbol::CSymbol* name; // ��� ������

		Symbol::CStorage < CVariableInformation* > methodParameters; // ��������� ������
		Symbol::CStorage < CVariableInformation* > localVariables; // ��������� ���������� ������

		Symbol::CSymbol* returnType; // ��� ������, ������� ������������
	};

	// ���������� � ����� � ���� ������ (���������� ������ ��� ���� ������)
	class CVariableInformation {
	public:
		CVariableInformation( std::string _type, std::string _name ) :
			type( Symbol::CSymbol::GetSymbol( _type ) ),
			name( Symbol::CSymbol::GetSymbol( _name ) ) {};
		std::string GetName() const { return name->GetString(); };

		Symbol::CSymbol* GetType() { return type; };
	private:
		Symbol::CSymbol* name; // ��� ����������
		Symbol::CSymbol* type; // ��� ������
	};
}