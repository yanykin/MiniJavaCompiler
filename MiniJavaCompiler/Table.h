/*
* �������� �������, ����������� ��� ��������� ������� �������� 
*/
#include <string>
#include <list>

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
	private:
		std::list < CClassInformation* > declaredClasses; // ����������� � ��������� ������
	};

	// ���������� � ���������� ������
	class CClassInformation {
	public:
		CClassInformation( std::string _name ) : name( _name ), isDerived(false) {};
		CClassInformation( std::string _name, std::string _baseClassName ) : name( _name ), baseClassName( _baseClassName ), isDerived( true ) {};
		std::string GetName() const { return name; };

		bool AddMethod( CMethodInformation* methodInfo );
		bool AddField( CVariableInformation* fieldInfo );
	private:
		std::string name; // ��� ������
		std::string baseClassName; // ������� �����, ���� ������������
		bool isDerived; // ����������� �� ���� ����� �� ������-�� ������� ������

		std::list < CVariableInformation* > fields; // ���� ������
		std::list < CMethodInformation* > methods; // ������ ������
	};

	// ���������� � ������ ������
	class CMethodInformation {
	public:
		CMethodInformation( std::string _name ) : name( _name ) {};
		std::string GetName() const { return name; };

		void SetReturnType( CType _returnType ) { returnType = _returnType; };

		bool AddParameter( CVariableInformation* param );
		bool AddLocalVariable( CVariableInformation* variable );

	private:
		std::string name; // ��� ������

		std::list < CVariableInformation* > methodParameters; // ��������� ������
		std::list < CVariableInformation* > localVariables; // ��������� ���������� ������

		CType returnType; // ��� ������, ������� ������������
	};

	// ���������� � ����� � ���� ������ (���������� ������ ��� ���� ������)
	class CVariableInformation {
	public:
		CVariableInformation(CType _type, std::string _name) : type(_type), name( _name ){};
		std::string GetName() const { return name;  };
	private:
		std::string name; // ��� ����������
		CType type; // ��� ������
	};
}