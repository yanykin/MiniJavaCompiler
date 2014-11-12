#include <iostream>
#include <cstdlib>
#include <cctype>
#include "Parser.hpp"

int main()
{
	int result = yyparse();
	if ( result == 0 ) {
		std::cout << "Success.";
	}
	else {
		std::cout << "Fail.";
	}
	return result;
}