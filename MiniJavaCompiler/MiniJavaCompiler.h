#pragma once

#include <string>
#include <iostream>
#include <cstdlib>
#include <cctype>
#include "Parser.hpp"

#include "SymbolTableBuilder.h"
#include "TypeChecker.h"
#include "PrettyPrinter.h"

#include "Translate.h"
#include "IRTreePrinter.h"

namespace MiniJavaCompiler {
	// Перечисление кодов ошибок
	enum TErrorCode {
		EC_NoError = 0,					// всё прошло успешно
		EC_ParseError = 1,			// ошибка в лексике
		EC_SyntaxError = 2,				// ошибка при синтаксическом анализе
		EC_TypeError = 3,				// ошибка при статической проверке типов
		EC_TransformToIRTreeError = 4,	// ошибка при преобразовании синтаксического дерево в IRTree
	};

	// Обёртка для всех вызовов всех необходимых методов
	class CMiniJavaCompiler
	{
	public:
		CMiniJavaCompiler();
		~CMiniJavaCompiler();

		// Собственно, компилирует код из sourceCodeFileName в файл с ассемблерным кодом
		TErrorCode Compile( const std::string& sourceCodeFileName, const std::string& asmOutputFileName );

	private:
		IProgram* syntaxTree; // корень построенного синтаксического дерева
		std::vector<Translate::CFragment> fragments; // фрагменты IR-дерева для каждого из методов
		std::map<Translate::CFragment*, const CStmList* > _canonizedFragments; // отображение "фрагмент" -> "канонизированное дерево"
		
		CSymbolTableBuilder *tableBuilder; // "посетитель" синтаксического дерева, который строит таблицу символов
		CTypeChecker *typeChecker; // "посетитель" синтаксического дерева, который проверяет типы данных
		Translate::CTranslate *translator; // "посетитель", который строит дерево промежуточного представления

		TErrorCode lastOccuredError; // код последней произошедшей ошибки
		TErrorCode GetLastError() { // возвращает код последней ошибки
			return lastOccuredError;
		}

		void parseToSyntaxTree(); // парсит дерево
		void createSymbolTable(); // строит таблицу символов (отображение "идентификатор" -> "тип данных")
		void checkTypes(); // проверяет типы данных
		void translateToIRTree(); // строит дерево промежуточного представления
		void simplifyIRTree(); // упрощает построенное IR-дерево к каноническому виду
	};
}


