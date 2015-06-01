#include "Temp.h"

using namespace Temp;

const std::string CTemp::suffix = "T";
const std::string CTemp::separator = "";
int CTemp::nextUniqueId = 0;

// Конструктор без параметров
CTemp::CTemp() {
	name = suffix + separator + std::to_string( nextUniqueId );
	nextUniqueId += 1;
}

// Конструктор, в котором мы передаём символ
CTemp::CTemp( const Symbol::CSymbol* symbol ) {
	name = symbol->GetString();
}

// CLabel

const std::string CLabel::suffix = "CLABEL";
const std::string CLabel::separator = "_";
int CLabel::nextUniqueId = 0;

// Конструктор без параметров
CLabel::CLabel() {
	name = suffix + separator + std::to_string( nextUniqueId );
	nextUniqueId += 1;
}

// Конструктор, в котором мы передаём символ
CLabel::CLabel( const Symbol::CSymbol* symbol ) {
	name = symbol->GetString();
}