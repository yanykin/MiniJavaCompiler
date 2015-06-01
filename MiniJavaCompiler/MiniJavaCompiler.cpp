#include "MiniJavaCompiler.h"
#include "Canon.h"

using namespace MiniJavaCompiler;

CMiniJavaCompiler::CMiniJavaCompiler() : lastOccuredError( EC_NoError )
{
}

CMiniJavaCompiler::~CMiniJavaCompiler()
{
}

TErrorCode CMiniJavaCompiler::Compile( const std::string& sourceCodeFileName, const std::string& asmOutputFileName ) {
	_sourceCodeFileName = sourceCodeFileName;
  	_asmOutputFileName = asmOutputFileName;

	lastOccuredError = EC_NoError;

	parseToSyntaxTree();
	createSymbolTable();
	checkTypes();
	translateToIRTree();
	simplifyIRTree();
	printIRTree();
	generateInstructions();

	return this->GetLastError();
}

void CMiniJavaCompiler::parseToSyntaxTree() {
	// Если ошибки на предыдущем шаге не произошло
	if ( lastOccuredError == EC_NoError ) {
		
		// Переопределяем переменную, отвечающую за источник входных данных
		yyin = fopen(_sourceCodeFileName.c_str(), "r");

		if ( yyin == nullptr ) {
			lastOccuredError = EC_SourceFileNotFoundError;
		}
		else {
			int result = yyparse( this->syntaxTree );
			lastOccuredError == 0 ? EC_NoError : EC_ParseError;
		}

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

void CMiniJavaCompiler::printIRTree()
{
	// Если ошибки на предыдущем шаге не произошло
	if( lastOccuredError == EC_NoError ) {
		CIRTreePrinter *irTreePrinter = new CIRTreePrinter( "graphviz.txt" );
		irTreePrinter->OpenFile();

		size_t methodsCounter = 1;
		for( auto& method : fragments ) {
			irTreePrinter->ResetPrinter( "fragment" + std::to_string( methodsCounter ) + "_", method.fullMethodName );
			method.rootStatement->Accept( irTreePrinter );
			methodsCounter += 1;
			irTreePrinter->WriteGraphStructureToTheFile();
		}
		irTreePrinter->CloseFile();
	}
}

void CMiniJavaCompiler::simplifyIRTree() {
	if ( lastOccuredError == EC_NoError ) {
		// Для каждого из фрагментов упрощаем дерево
		for ( auto fragment : fragments ) {
			
			Canon::CCanon canonizer( fragment.rootStatement, fragment.methodFrame );
			canonizer.Canonize();
			_canonizedFragments[&fragment] = canonizer.GetCanonizedStatements();
		}
	}
}

void CMiniJavaCompiler::generateInstructions() {
	if ( lastOccuredError == EC_NoError ) {
		// Для каждого из фрагментов
		for ( auto fragment : _canonizedFragments ) {
			// Создаём генератор кода
			CodeGeneration::CCodeGenerator generator( fragment.second, fragment.first->methodFrame );
			generator.Generate();
			// Список инструкций
			_instructionLists[ fragment.first ] = generator.GetInstrucions();
		}
	}
}

void CMiniJavaCompiler::writeInstrucions() {
	if ( lastOccuredError == EC_NoError ) {
		// Открываем файл для записи
		std::ofstream asmOutputFile( _asmOutputFileName );
		// Если файл удалось открыть
		if ( asmOutputFile ) {
			for ( auto fragment : _instructionLists ) {
				// Сначала записываем имя метода
				asmOutputFile << "[" << fragment.first->fullMethodName << "]" << std::endl;
				// Далее записываем все команды
				for ( auto command : fragment.second ) {
					std::string commandString = command->Format(new Temp::CDefaultTempMap());
				}
			}
			// Разделитель между методами
			asmOutputFile << std::endl;
			asmOutputFile.close();
		}
		else {
			lastOccuredError = EC_AsmOutputFileError;
		}
	}
}