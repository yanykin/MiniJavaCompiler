/*
* ќписание классов, необходимых дл€ поддержки таблицы символов 
*/
#pragma once
#include <string>
#include <list>
#include <map>

// “аблица символов дл€ €зыка MiniJava
namespace CSymbolsTable {

	// ѕредопределение
	class CClassInformation;
	class CMethodInformation;
	class CVariableInformation;

	enum TVariableType {
		VAR_TYPE_INTEGER,			// целочисленна€ переменна€
		VAR_TYPE_INTEGER_ARRAY,	// массив из целых чисел
		VAR_TYPE_BOOLEAN,			// булев тип
		VAR_TYPE_CLASS			// класс
	};

	struct CType {
		TVariableType type; // тип переменной
		std::string className; // класс, если это переменна€ типа класса
	};

	// —писок известных классов
	class CTable {
	public:
		CTable() : declaredClasses() {};

		// ƒобавл€ет класс в таблицу символов и возвращает флаг успеха/неуспеха
		bool AddClass( CClassInformation *classInfo );

		// ¬озвращает ссылку на структуру с информацией класса или null, если такой класс не нашли
		CClassInformation* GetClassByName(std::string& className);

	private:
		std::map < std::string, CClassInformation* > declaredClasses; // определЄнные в программе классы
	};

	// »нформаци€ о конкретном классе
	class CClassInformation {
	public:
		CClassInformation( std::string _name ) : name( _name ), isDerived(false) {};
		CClassInformation( std::string _name, std::string _baseClassName ) : name( _name ), baseClassName( _baseClassName ), isDerived( true ) {};
		std::string GetName() const { return name; };

		bool AddMethod( CMethodInformation* methodInfo );
		bool AddField( CVariableInformation* fieldInfo );

		// ¬озвращает ссылку на структуру с информацией метода класса или null в противном случае
		CMethodInformation* GetMethodByName( std::string& methodName );
		// ¬озвращает тип данных дл€ локальной переменной
		CType* GetFieldType( std::string& fieldName );

	private:
		std::string name; // им€ класса
		std::string baseClassName; // базовый класс, если используетс€
		bool isDerived; // унаследован ли этот класс от какого-то другого класса

		std::map < std::string, CVariableInformation* > fields; // пол€ класса
		std::map < std::string, CMethodInformation* > methods; // методы класса
	};

	// »нформаци€ о методе класса
	class CMethodInformation {
	public:
		CMethodInformation( std::string _name ) : name( _name ) {};
		std::string GetName() const { return name; };

		void SetReturnType( CType *_returnType ) { returnType = _returnType; };

		bool AddParameter( CVariableInformation* param );
		bool AddLocalVariable( CVariableInformation* variable );

		// ¬озвращает информацию о типе аргумента, null, если такого аргумента нет
		CType* GetArgumentType( std::string& argumentName );
		// јналогично и дл€ локальных переменных метода
		CType* GetLocalVariableType( std::string& variableName );

	private:
		std::string name; // им€ метода

		std::map < std::string, CVariableInformation* > methodParameters; // параметры метода
		std::map < std::string, CVariableInformation* > localVariables; // локальные переменные метода

		CType* returnType; // тип данных, который возвращаетс€
	};

	// »нформаци€ о имени и типе данных (переменна€ метода или поле класса)
	class CVariableInformation {
	public:
		CVariableInformation(CType* _type, std::string _name) : type(_type), name( _name ){};
		std::string GetName() const { return name;  };

		CType* GetType() { return type; };
	private:
		std::string name; // им€ переменной
		CType* type; // тип данных
	};
}