#include "CoordinatesHolder.h"
#include "Parser.hpp"


CCoordinatesHolder::CCoordinatesHolder( const YYLTYPE& yylloc ) {
	column = yylloc.first_column;
	row = yylloc.first_line;
}