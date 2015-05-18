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
}

void CMiniJavaCompiler::parseToSyntaxTree() {
	// Если ошибки на предыдущем шаге не произошло
	if ( lastOccuredError == EC_NoError ) {
		int result = yyparse( this->syntaxTree );
		lastOccuredError == 0 ? EC_NoError : EC_ParseError;
	}
}

void CMiniJavaCompiler::createSymbolTable() {
	// Если ошибки на предыдущем шаге не произошло
	if ( lastOccuredError == EC_NoError ) {
		tableBuilder = new CSymbolTableBuilder();
		syntaxTree->Accept( tableBuilder );
		lastOccuredError = tableBuilder->IsTableCorrect() ? EC_NoError : EC_SyntaxError;
	}
}

void CMiniJavaCompiler::checkTypes() {
	// Если ошибки на предыдущем шаге не произошло
	if ( lastOccuredError == EC_NoError ) {
		typeChecker = new CTypeChecker( tableBuilder->GetConstructedTable() );
		syntaxTree->Accept( typeChecker );
		lastOccuredError = typeChecker->IsAllCorrect() ? EC_NoError : EC_TypeError;
	}
}

void CMiniJavaCompiler::translateToIRTree() {
	// Если ошибки на предыдущем шаге не произошло
	if ( lastOccuredError == EC_NoError ) {
		// Строим дерево промежуточного представления
		Translate::CTranslate *translator = new Translate::CTranslate( tableBuilder->GetConstructedTable() );
		syntaxTree->Accept( translator );
		fragments = translator->Methods;
	}
}

void CMiniJavaCompiler::simplifyIRTree() {
	if ( lastOccuredError == EC_NoError ) {
		// Для каждого из фрагментов упрощаем дерево
		for ( auto fragment : fragments ) {
			
			// Упорядочиваем в линию
			const IRTree::CStmList* statementList = Canon::CCanon::Linearize( fragment.rootStatement );

			// Разбиваем на базовые блоки
			Canon::CStatementsSplitter splitter( fragment.methodFrame, statementList );

		}
	}
}