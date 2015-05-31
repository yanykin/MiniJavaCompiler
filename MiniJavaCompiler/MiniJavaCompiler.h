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

// ��������� ������� ����� ������������ ����������� � ���� ����������
extern FILE* yyin;

namespace MiniJavaCompiler {
	

	// ������������ ����� ������
	enum TErrorCode {
		EC_NoError = 0,					// �� ������ �������
		EC_SourceFileNotFoundError = 1,
		EC_ParseError = 2,			// ������ � �������
		EC_SyntaxError = 3,				// ������ ��� �������������� �������
		EC_TypeError = 4,				// ������ ��� ����������� �������� �����
		EC_TransformToIRTreeError = 5,	// ������ ��� �������������� ��������������� ������ � IRTree
		EC_AsmOutputFileError = 6, // ������, ����������� ��� ������ ���������� � ����
	};

	// ������ ��� ���� ������� ���� ����������� �������
	class CMiniJavaCompiler
	{
	public:
		CMiniJavaCompiler();
		~CMiniJavaCompiler();

		// ����������, ����������� ��� �� sourceCodeFileName � ���� � ������������ �����
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

		IProgram* syntaxTree; // ������ ������������ ��������������� ������
		std::vector<Translate::CFragment> fragments; // ��������� IR-������ ��� ������� �� �������
		std::map<Translate::CFragment*, const IRTree::CStmList* > _canonizedFragments; // ����������� "��������" -> "���������������� ������"
		std::map <Translate::CFragment*, CodeGeneration::TInstructionsList > _instructionLists; // ��� ������� ��������� ������ ������ ��������������� ����������
		
		CSymbolTableBuilder *tableBuilder; // "����������" ��������������� ������, ������� ������ ������� ��������
		CTypeChecker *typeChecker; // "����������" ��������������� ������, ������� ��������� ���� ������
		Translate::CTranslate *translator; // "����������", ������� ������ ������ �������������� �������������

		TErrorCode lastOccuredError; // ��� ��������� ������������ ������
		TErrorCode GetLastError() { // ���������� ��� ��������� ������
			return lastOccuredError;
		}

		void parseToSyntaxTree(); // ������ ������
		void createSymbolTable(); // ������ ������� �������� (����������� "�������������" -> "��� ������")
		void checkTypes(); // ��������� ���� ������
		void translateToIRTree(); // ������ ������ �������������� �������������
		void printIRTree(); // �������� ������ �������������� �������������
		void simplifyIRTree(); // �������� ����������� IR-������ � ������������� ����
		void generateInstructions(); // ���������� ������� ����������

		void writeInstrucions(); // ���������� ���������� ������� � ����
	};
}


