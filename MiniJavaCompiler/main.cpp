#include <iostream>
#include <cstdlib>
#include <cctype>
#include "Parser.hpp"

#include "SymbolTableBuilder.h"
#include "TypeChecker.h"

int main()
{
	IProgram* mainProgram = 0;
	int result = yyparse(mainProgram);

	if ( result == 0 ) {
		/*
		std::cout << "Success." << std::endl;
		std::cout << "Reducing for starting token." << std::endl;
		*/

		
		CPrettyPrinter *prettyPrinter = new CPrettyPrinter();
		mainProgram->Accept( prettyPrinter );
		delete prettyPrinter;
		

		CSymbolTableBuilder *tableBuilder = new CSymbolTableBuilder();
		mainProgram->Accept( tableBuilder );
		if ( tableBuilder->IsTableCorrect() ) {
			CTypeChecker *typeChecker = new CTypeChecker( tableBuilder->GetConstructedTable() );
			mainProgram->Accept( typeChecker );
			if ( typeChecker->IsAllCorrect() ) {
				std::cout << "Program is correct! :)" << std::endl;
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