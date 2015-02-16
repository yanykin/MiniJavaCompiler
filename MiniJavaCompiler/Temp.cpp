#include "Temp.h"

using namespace Temp;

const std::string CTemp::suffix = "CTEMP";
const std::string CTemp::separator = "_";
int CTemp::nextUniqueId = 0;

// ����������� ��� ����������
CTemp::CTemp() {
	name = suffix + "_" + std::to_string( nextUniqueId );
	nextUniqueId;
}

// �����������, � ������� �� ������� ������
CTemp::CTemp( const Symbol::CSymbol* symbol ) {
	name = symbol->GetString();
}

// CLabel

const std::string CLabel::suffix = "CLABEL";
const std::string CLabel::separator = "_";
int CLabel::nextUniqueId = 0;

// ����������� ��� ����������
CLabel::CLabel() {
	name = suffix + "_" + std::to_string( nextUniqueId );
	nextUniqueId;
}

// �����������, � ������� �� ������� ������
CLabel::CLabel( const Symbol::CSymbol* symbol ) {
	name = symbol->GetString();
}