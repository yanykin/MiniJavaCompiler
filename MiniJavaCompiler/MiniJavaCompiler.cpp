#include "MiniJavaCompiler.h"
#include "Canon.h"

using namespace MiniJavaCompiler;

CMiniJavaCompiler::CMiniJavaCompiler()
{
}

CMiniJavaCompiler::~CMiniJavaCompiler()
{
}

TErrorCode CMiniJavaCompiler::Compile( const std::string& sourceCodeFileName, const std::string& asmOutputFileName ) {
	parseToSyntaxTree();
	createSymbolTable();
	checkTypes();
	translateToIRTree();
	simplifyIRTree();
	return this->GetLastError();
}

void CMiniJavaCompiler::parseToSyntaxTree() {
	// ���� ������ �� ���������� ���� �� ���������
	if ( lastOccuredError == EC_NoError ) {
		int result = yyparse( this->syntaxTree );
		lastOccuredError == 0 ? EC_NoError : EC_ParseError;
	}
}

void CMiniJavaCompiler::createSymbolTable() {
	// ���� ������ �� ���������� ���� �� ���������
	if ( lastOccuredError == EC_NoError ) {
		tableBuilder = new CSymbolTableBuilder();
		syntaxTree->Accept( tableBuilder );
		lastOccuredError = tableBuilder->IsTableCorrect() ? EC_NoError : EC_SyntaxError;
	}
}

void CMiniJavaCompiler::checkTypes() {
	// ���� ������ �� ���������� ���� �� ���������
	if ( lastOccuredError == EC_NoError ) {
		typeChecker = new CTypeChecker( tableBuilder->GetConstructedTable() );
		syntaxTree->Accept( typeChecker );
		lastOccuredError = typeChecker->IsAllCorrect() ? EC_NoError : EC_TypeError;
	}
}

void CMiniJavaCompiler::translateToIRTree() {
	// ���� ������ �� ���������� ���� �� ���������
	if ( lastOccuredError == EC_NoError ) {
		// ������ ������ �������������� �������������
		Translate::CTranslate *translator = new Translate::CTranslate( tableBuilder->GetConstructedTable() );
		syntaxTree->Accept( translator );
		fragments = translator->Methods;
	}
}

void CMiniJavaCompiler::simplifyIRTree() {
	if ( lastOccuredError == EC_NoError ) {
		// ��� ������� �� ���������� �������� ������
		for ( auto fragment : fragments ) {
			
			Canon::CCanon canonizer( fragment.rootStatement, fragment.methodFrame );
			canonizer.Canonize();
			_canonizedFragments[&fragment] = canonizer.GetCanonizedStatements();
		}
	}
}