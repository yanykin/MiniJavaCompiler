/*
* �������� �������, ����������� ��� ��������� ������� �������� 
*/
#pragma once
#include <string>
#include <list>
#include <map>

// ������� �������� ��� ����� MiniJava
namespace CSymbolsTable {

	// ���������������
	class CClassInformation;
	class CMethodInformation;
	class CVariableInformation;

	enum TVariableType {
		VAR_TYPE_INTEGER,			// ������������� ����������
		VAR_TYPE_INTEGER_ARRAY,	// ������ �� ����� �����
		VAR_TYPE_BOOLEAN,			// ����� ���
		VAR_TYPE_CLASS			// �����
	};

	struct CType {
		TVariableType type; // ��� ����������
		std::string className; // �����, ���� ��� ���������� ���� ������
	};

	// ������ ��������� �������
	class CTable {
	public:
		CTable() : declaredClasses() {};

		// ��������� ����� � ������� �������� � ���������� ���� ������/��������
		bool AddClass( CClassInformation *classInfo );

		// ���������� ������ �� ��������� � ����������� ������ ��� null, ���� ����� ����� �� �����
		CClassInformation* GetClassByName(std::string& className);

	private:
		std::map < std::string, CClassInformation* > declaredClasses; // ����������� � ��������� ������
	};

	// ���������� � ���������� ������
	class CClassInformation {
	public:
		CClassInformation( std::string _name ) : name( _name ), isDerived(false) {};
		CClassInformation( std::string _name, std::string _baseClassName ) : name( _name ), baseClassName( _baseClassName ), isDerived( true ) {};
		std::string GetName() const { return name; };

		bool AddMethod( CMethodInformation* methodInfo );
		bool AddField( CVariableInformation* fieldInfo );

		// ���������� ������ �� ��������� � ����������� ������ ������ ��� null � ��������� ������
		CMethodInformation* GetMethodByName( std::string& methodName );
		// ���������� ��� ������ ��� ��������� ����������
		CType* GetFieldType( std::string& fieldName );

		

	private:
		std::string name; // ��� ������
		std::string baseClassName; // ������� �����, ���� ������������
		bool isDerived; // ����������� �� ���� ����� �� ������-�� ������� ������

		std::map < std::string, CVariableInformation* > fields; // ���� ������
		std::map < std::string, CMethodInformation* > methods; // ������ ������
	};

	// ���������� � ������ ������
	class CMethodInformation {
	public:
		CMethodInformation( std::string _name ) : name( _name ) {};
		std::string GetName() const { return name; };

		void SetReturnType( CType *_returnType ) { returnType = _returnType; }
		CType* GetReturnType() const { return returnType; };

		bool AddParameter( CVariableInformation* param );
		bool AddLocalVariable( CVariableInformation* variable );

		// ���������� ���������� � ���� ���������, null, ���� ������ ��������� ���
		CType* GetArgumentType( std::string& argumentName );
		// ���������� � ��� ��������� ���������� ������
		CType* GetLocalVariableType( std::string& variableName );

	private:
		std::string name; // ��� ������

		std::map < std::string, CVariableInformation* > methodParameters; // ��������� ������
		std::map < std::string, CVariableInformation* > localVariables; // ��������� ���������� ������

		CType* returnType; // ��� ������, ������� ������������
	};

	// ���������� � ����� � ���� ������ (���������� ������ ��� ���� ������)
	class CVariableInformation {
	public:
		CVariableInformation(CType* _type, std::string _name) : type(_type), name( _name ){};
		std::string GetName() const { return name;  };

		CType* GetType() { return type; };
	private:
		std::string name; // ��� ����������
		CType* type; // ��� ������
	};
}