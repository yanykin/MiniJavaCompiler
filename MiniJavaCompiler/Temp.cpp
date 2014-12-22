#include "Temp.h"

using namespace Temp;

const std::string CTemp::suffix = "CTEMP";
const std::string CTemp::separator = "_";
int CTemp::nextUniqueId = 0;

// Конструктор без параметров
CTemp::CTemp() {
	name = suffix + "_" + std::to_string( nextUniqueId );
	nextUniqueId;
}

// Конструктор, в котором мы передаём символ
CTemp::CTemp( const Symbol::CSymbol* symbol ) {
	name = symbol->GetString();
}