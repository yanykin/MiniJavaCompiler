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

#include "Instruction.h"

// Связывает входной поток лексического анализатора с этой переменной
extern FILE* yyin;

namespace MiniJavaCompiler {
	

	// Перечисление кодов ошибок
	enum TErrorCode {
		EC_NoError = 0,					// всё прошло успешно
		EC_SourceFileNotFoundError = 1,
		EC_ParseError = 2,			// ошибка в лексике
		EC_SyntaxError = 3,				// ошибка при синтаксическом анализе
		EC_TypeError = 4,				// ошибка при статической проверке типов
		EC_TransformToIRTreeError = 5,	// ошибка при преобразовании синтаксического дерево в IRTree
		EC_AsmOutputFileError = 6, // ошибка, возникающая при записи инструкций в файл
	};

	// Обёртка для всех вызовов всех необходимых методов
	class CMiniJavaCompiler
	{
	public:
		CMiniJavaCompiler();
		~CMiniJavaCompiler();

		// Собственно, компилирует код из sourceCodeFileName в файл с ассемблерным кодом
		TErrorCode Compile( const std::string& sourceCodeFileName, const std::string& asmOutputFileName );

		std::string static GetCodeDescription( TErrorCode code ) {
			switch ( code )
			{
			case EC_NoError:
				return "No error";
			case EC_SourceFileNotFoundError:
				return "Unable to open source file";
			case EC_ParseError:
				return "Parsing error";
			case EC_SyntaxError:
				return "Syntax error";
			case EC_TypeError:
				return "Type checking error";
			case EC_TransformToIRTreeError:
				return "Transformation to IR Tree error";
			case EC_AsmOutputFileError:
				return "Unable to write assembler instructions to the file";
			default:
				return "Unknown error code";
			}
		}

	private:
		std::string _sourceCodeFileName;
		std::string _asmOutputFileName;

		IProgram* syntaxTree; // корень построенного синтаксического дерева
		std::vector<Translate::CFragment> fragments; // фрагменты IR-дерева для каждого из методов
		std::map<Translate::CFragment*, const CStmList* > _canonizedFragments; // отображение "фрагмент" -> "канонизированное дерево"
		std::map <Translate::CFragment*, CodeGeneration::TInstructionsList > _instructionLists; // для каждого фрагмента хранит список сгенерированных инструкций
		
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
		void generateInstructions(); // генерирует команды ассемблера

		void writeInstrucions(); // записывает полученные команды в файл
	};
}


