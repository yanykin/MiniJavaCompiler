/*
* Описание классов, необходимых для поддержки таблицы символов 
*/
#pragma once
#include <string>
#include <list>
#include <map>

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

		// Возвращает ссылку на структуру с информацией класса или null, если такой класс не нашли
		CClassInformation* GetClassByName(std::string& className);

	private:
		std::map < std::string, CClassInformation* > declaredClasses; // определённые в программе классы
	};

	// Информация о конкретном классе
	class CClassInformation {
	public:
		CClassInformation( std::string _name ) : name( _name ), isDerived(false) {};
		CClassInformation( std::string _name, std::string _baseClassName ) : name( _name ), baseClassName( _baseClassName ), isDerived( true ) {};
		std::string GetName() const { return name; };

		bool AddMethod( CMethodInformation* methodInfo );
		bool AddField( CVariableInformation* fieldInfo );

		// Возвращает ссылку на структуру с информацией метода класса или null в противном случае
		CMethodInformation* GetMethodByName( std::string& methodName );
		// Возвращает тип данных для локальной переменной
		CType* GetFieldType( std::string& fieldName );

		

	private:
		std::string name; // имя класса
		std::string baseClassName; // базовый класс, если используется
		bool isDerived; // унаследован ли этот класс от какого-то другого класса

		std::map < std::string, CVariableInformation* > fields; // поля класса
		std::map < std::string, CMethodInformation* > methods; // методы класса
	};

	// Информация о методе класса
	class CMethodInformation {
	public:
		CMethodInformation( std::string _name ) : name( _name ) {};
		std::string GetName() const { return name; };

		void SetReturnType( CType *_returnType ) { returnType = _returnType; }
		CType* GetReturnType() const { return returnType; };

		bool AddParameter( CVariableInformation* param );
		bool AddLocalVariable( CVariableInformation* variable );

		// Возвращает информацию о типе аргумента, null, если такого аргумента нет
		CType* GetArgumentType( std::string& argumentName );
		// Аналогично и для локальных переменных метода
		CType* GetLocalVariableType( std::string& variableName );

	private:
		std::string name; // имя метода

		std::map < std::string, CVariableInformation* > methodParameters; // параметры метода
		std::map < std::string, CVariableInformation* > localVariables; // локальные переменные метода

		CType* returnType; // тип данных, который возвращается
	};

	// Информация о имени и типе данных (переменная метода или поле класса)
	class CVariableInformation {
	public:
		CVariableInformation(CType* _type, std::string _name) : type(_type), name( _name ){};
		std::string GetName() const { return name;  };

		CType* GetType() { return type; };
	private:
		std::string name; // имя переменной
		CType* type; // тип данных
	};
}