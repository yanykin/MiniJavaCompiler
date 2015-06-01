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
	writeInstrucions();
    generateControlFlowGraph();

	return this->GetLastError();
}

void CMiniJavaCompiler::parseToSyntaxTree() {
	// ���� ������ �� ���������� ���� �� ���������
	if ( lastOccuredError == EC_NoError ) {
		
		// �������������� ����������, ���������� �� �������� ������� ������
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

void CMiniJavaCompiler::printIRTree()
{
	// ���� ������ �� ���������� ���� �� ���������
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
		// ��� ������� �� ���������� �������� ������
		for ( auto& fragment : fragments ) {
			
			Canon::CCanon canonizer( fragment.rootStatement, fragment.methodFrame );
			canonizer.Canonize();
			_canonizedFragments[&fragment] = canonizer.GetCanonizedStatements();
		}
	}
}

void CMiniJavaCompiler::generateInstructions() {
	if ( lastOccuredError == EC_NoError ) {
		// ��� ������� �� ����������
		for ( auto fragment : _canonizedFragments ) {
			// ������ ��������� ����
			CodeGeneration::CCodeGenerator generator( fragment.second, fragment.first->methodFrame );
			generator.Generate();
			// ������ ����������
			_instructionLists[ fragment.first ] = generator.GetInstrucions();
		}
	}
}

void CMiniJavaCompiler::generateControlFlowGraph() {
    if( lastOccuredError == EC_NoError ) {
        // ��� ������� �� ���������� ������ ���
        for( auto fragment : _canonizedFragments ) {
            RegisterAllocation::CControlFlowGraphBuilder graphBuilder;
            graphBuilder.Build( _instructionLists[fragment.first] );
            _controlFlowGraphs[fragment.first] = graphBuilder.Get();
        }
    }
}

void CMiniJavaCompiler::writeInstrucions() {
	if ( lastOccuredError == EC_NoError ) {
		// ��������� ���� ��� ������
		std::ofstream asmOutputFile( _asmOutputFileName );
		// ���� ���� ������� �������
		if ( asmOutputFile ) {
			for ( auto fragment : _instructionLists ) {
				// ������� ���������� ��� ������
				asmOutputFile << "[" << fragment.first->fullMethodName << "]" << std::endl;
				// ����� ���������� ��� �������
				for ( auto command : fragment.second ) {
					std::string commandString = command->Format(new Temp::CDefaultTempMap());
					asmOutputFile << commandString << std::endl;
				}
			}
			// ����������� ����� ��������
			asmOutputFile << std::endl;
			asmOutputFile.close();
		}
		else {
			lastOccuredError = EC_AsmOutputFileError;
		}
	}
}