/*
* Интерфейс для доступа к элементам таблицы символов, предназначенного для анализа кода после построения
* синтаксического дерева
*/
#pragma once
#include <string>
#include <unordered_map>

namespace Symbol {

	// Отдельный символ, на который отображаются строки 
	class CSymbol {
	public:
		// Возвращает символ по заданной строке
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

		// Возвращает строку для текущего символа
		const std::string& GetString() const { return string_key; };
	private:
		// Приватный конструктор
		CSymbol( const std::string& s ) : string_key( s ) {};

		// Строка, по которой находится символ
		const std::string& string_key;

		// Таблица для строк
		static std::unordered_map<std::string, CSymbol*> mapping;
		
	};

	// Некое хранилище символов
	template<class TObject>
	class CStorage {
	public:
		// Создаёт хранилище символов, где ключами служат CSymbol, а значениями - объекты типа TObject
		CStorage<TObject>() {};
		// Вставляет объект по указанному ключу
		void InsertObject( CSymbol* symbol, TObject value ) {
			table[ symbol ] = value;
		};
		// Возвращает указатель на объект
		TObject GetObject( CSymbol* symbol ) const {
			auto result = table.find( symbol );
			return result != table.end() ? result->second : NULL;
		};

	private:
		std::unordered_map<CSymbol*, TObject> table;
	};
}