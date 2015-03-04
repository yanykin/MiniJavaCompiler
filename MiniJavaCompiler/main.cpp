#include <iostream>
#include <cstdlib>
#include <cctype>
#include "Parser.hpp"

#include "SymbolTableBuilder.h"
#include "TypeChecker.h"
#include "PrettyPrinter.h"

#include "Translate.h"
#include "IRTreePrinter.h"

int main()
{
	IProgram* mainProgram = 0;
	int result = yyparse(mainProgram);

	if ( result == 0 ) {
		/*
		std::cout << "Success." << std::endl;
		std::cout << "Reducing for starting token." << std::endl;
		*/

		CPrettyPrinter prettyPrinter;
		mainProgram->Accept( &prettyPrinter );
		

		CSymbolTableBuilder *tableBuilder = new CSymbolTableBuilder();
		mainProgram->Accept( tableBuilder );
		if ( tableBuilder->IsTableCorrect() ) {
			CTypeChecker *typeChecker = new CTypeChecker( tableBuilder->GetConstructedTable() );
			mainProgram->Accept( typeChecker );
			if ( typeChecker->IsAllCorrect() ) {
				std::cout << "Program is correct! :)" << std::endl;

				// —троим дерево промежуточного представлени€
				CTranslate *translator = new CTranslate( tableBuilder->GetConstructedTable() );
				mainProgram->Accept( translator );
				CIRTreePrinter *irTreePrinter = new CIRTreePrinter( "graphviz.txt" );
				if ( !translator->Methods.empty() ) {
					translator->Methods[ 0 ].second->Accept( irTreePrinter );
				}
				irTreePrinter->WriteGraphStructureToTheFile();
				
			}
			delete typeChecker;
		}
		delete tableBuilder;
	}
	else {
		std::cout << "Fail." << std::endl;
	}
	fflush( stdout );
	// std::cin.ignore( std::numeric_limits<std::streamsize>::max() );
	system( "pause" );
	return result;
}