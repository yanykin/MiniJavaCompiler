/*
* Описание классов, необходимых для поддержки таблицы символов 
*/
#include <string>
#include <list>

// Таблица символов для языка MiniJava
namespace CSymbolsTable {

	// Предопределение
	class CClassInformation;
	class CMethodInformation;
	class CVariableInformation;

	enum TVariableType {
		VAR_TYPE_INTEGER,			// целочисленная переменная
		VAR_TYPE_INTEGER_ARRAY,	// массив из целых чисел
		VAR_TYPE_BOOLEAN,			// булев тип
		VAR_TYPE_CLASS			// класс
	};

	struct CType {
		TVariableType type; // тип переменной
		std::string className; // класс, если это переменная типа класса
	};

	// Список известных классов
	class CTable {
	public:
		CTable() : declaredClasses() {};

		// Добавляет класс в таблицу символов и возвращает флаг успеха/неуспеха
		bool AddClass( CClassInformation *classInfo );
	private:
		std::list < CClassInformation* > declaredClasses; // определённые в программе классы
	};

	// Информация о конкретном классе
	class CClassInformation {
	public:
		CClassInformation( std::string _name ) : name( _name ), isDerived(false) {};
		CClassInformation( std::string _name, std::string _baseClassName ) : name( _name ), baseClassName( _baseClassName ), isDerived( true ) {};
		std::string GetName() const { return name; };

		bool AddMethod( CMethodInformation* methodInfo );
		bool AddField( CVariableInformation* fieldInfo );
	private:
		std::string name; // имя класса
		std::string baseClassName; // базовый класс, если используется
		bool isDerived; // унаследован ли этот класс от какого-то другого класса

		std::list < CVariableInformation* > fields; // поля класса
		std::list < CMethodInformation* > methods; // методы класса
	};

	// Информация о методе класса
	class CMethodInformation {
	public:
		CMethodInformation( std::string _name ) : name( _name ) {};
		std::string GetName() const { return name; };

		void SetReturnType( CType _returnType ) { returnType = _returnType; };

		bool AddParameter( CVariableInformation* param );
		bool AddLocalVariable( CVariableInformation* variable );

	private:
		std::string name; // имя метода

		std::list < CVariableInformation* > methodParameters; // параметры метода
		std::list < CVariableInformation* > localVariables; // локальные переменные метода

		CType returnType; // тип данных, который возвращается
	};

	// Информация о имени и типе данных (переменная метода или поле класса)
	class CVariableInformation {
	public:
		CVariableInformation(CType _type, std::string _name) : type(_type), name( _name ){};
		std::string GetName() const { return name;  };
	private:
		std::string name; // имя переменной
		CType type; // тип данных
	};
}