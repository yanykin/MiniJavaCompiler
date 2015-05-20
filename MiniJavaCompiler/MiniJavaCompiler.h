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
	// ������������ ����� ������
	enum TErrorCode {
		EC_NoError = 0,					// �� ������ �������
		EC_ParseError = 1,			// ������ � �������
		EC_SyntaxError = 2,				// ������ ��� �������������� �������
		EC_TypeError = 3,				// ������ ��� ����������� �������� �����
		EC_TransformToIRTreeError = 4,	// ������ ��� �������������� ��������������� ������ � IRTree
	};

	// ������ ��� ���� ������� ���� ����������� �������
	class CMiniJavaCompiler
	{
	public:
		CMiniJavaCompiler();
		~CMiniJavaCompiler();

		// ����������, ����������� ��� �� sourceCodeFileName � ���� � ������������ �����
		TErrorCode Compile( const std::string& sourceCodeFileName, const std::string& asmOutputFileName );

	private:
		IProgram* syntaxTree; // ������ ������������ ��������������� ������
		std::vector<Translate::CFragment> fragments; // ��������� IR-������ ��� ������� �� �������
		std::map<Translate::CFragment*, const CStmList* > _canonizedFragments; // ����������� "��������" -> "���������������� ������"
		
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
		void simplifyIRTree(); // �������� ����������� IR-������ � ������������� ����
	};
}


