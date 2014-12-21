/*
* Описание классов, необходимых для поддержки таблицы символов 
*/
#pragma once
#include <string>
#include <list>
#include <map>

#include "Symbol.h"

// Таблица символов для языка MiniJava
namespace CSymbolsTable {

	// Предопределение
	class CClassInformation;
	class CMethodInformation;
	class CVariableInformation;

	// Список известных классов
	class CTable {
	public:
		CTable() : declaredClasses() {};

		// Добавляет класс в таблицу символов и возвращает флаг успеха/неуспеха
		bool AddClass( CClassInformation *classInfo );

		// Возвращает ссылку на структуру с информацией класса или null, если такой класс не нашли
		CClassInformation* GetClassByName(const std::string& className);

	private:
		Symbol::CStorage < CClassInformation* > declaredClasses; // определённые в программе классы
	};

	// Информация о конкретном классе
	class CClassInformation {
	public:
		CClassInformation( std::string _name ) : name( Symbol::CSymbol::GetSymbol(_name) ), isDerived(false) {};
		CClassInformation( std::string _name, std::string _baseClassName ) :
			name( Symbol::CSymbol::GetSymbol( _name ) ),
			baseClassName( Symbol::CSymbol::GetSymbol(_baseClassName) ),
			isDerived( true ) {};
		std::string GetName() const { return name->GetString(); };

		bool AddMethod( CMethodInformation* methodInfo );
		bool AddField( CVariableInformation* fieldInfo );

		// Возвращает ссылку на структуру с информацией метода класса или null в противном случае
		CMethodInformation* GetMethodByName( std::string& methodName );
		// Возвращает тип данных для локальной переменной
		Symbol::CSymbol* GetFieldType( std::string& fieldName );		

	private:
		Symbol::CSymbol* name; // имя класса
		Symbol::CSymbol* baseClassName; // базовый класс, если используется

		bool isDerived; // унаследован ли этот класс от какого-то другого класса

		Symbol::CStorage < CVariableInformation* > fields; // поля класса
		Symbol::CStorage < CMethodInformation* > methods; // методы класса
	};

	// Информация о методе класса
	class CMethodInformation {
	public:
		CMethodInformation( std::string _name ) : name( Symbol::CSymbol::GetSymbol(_name) ) {};
		std::string GetName() const { return name->GetString(); };

		void SetReturnType( Symbol::CSymbol* _returnType ) { returnType = _returnType; }
		Symbol::CSymbol* GetReturnType() const { return returnType; };

		bool AddParameter( CVariableInformation* param );
		bool AddLocalVariable( CVariableInformation* variable );

		// Возвращает информацию о типе аргумента, null, если такого аргумента нет
		Symbol::CSymbol* GetArgumentType( const std::string& argumentName );
		// Аналогично и для локальных переменных метода
		Symbol::CSymbol* GetLocalVariableType( const std::string& variableName );

	private:
		Symbol::CSymbol* name; // имя метода

		Symbol::CStorage < CVariableInformation* > methodParameters; // параметры метода
		Symbol::CStorage < CVariableInformation* > localVariables; // локальные переменные метода

		Symbol::CSymbol* returnType; // тип данных, который возвращается
	};

	// Информация о имени и типе данных (переменная метода или поле класса)
	class CVariableInformation {
	public:
		CVariableInformation( std::string _type, std::string _name ) :
			type( Symbol::CSymbol::GetSymbol( _type ) ),
			name( Symbol::CSymbol::GetSymbol( _name ) ) {};
		std::string GetName() const { return name->GetString();  };

		Symbol::CSymbol* GetType() { return type; };
	private:
		Symbol::CSymbol* name; // имя переменной
		Symbol::CSymbol* type; // тип данных
	};
}