#include <iostream>
#include <cstdlib>
#include <cctype>
#include "Parser.hpp"

int main()
{
	IProgram* mainProgram = 0;
	int result = yyparse(mainProgram);

	if ( result == 0 ) {
		std::cout << "Success." << std::endl;
	}
	else {
		std::cout << "Fail." << std::endl;
	}

	std::cout << "Reducing for starting token" << std::endl;
	CPrettyPrinter *prettyPrinter = new CPrettyPrinter();
	mainProgram->Accept( prettyPrinter );
	delete prettyPrinter;

	fflush( stdout );
	// std::cin.ignore( std::numeric_limits<std::streamsize>::max() );
	system( "pause" );
	return result;
}