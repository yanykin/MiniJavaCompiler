#include "Temp.h"

using namespace Temp;

const std::string CTemp::suffix = "CTEMP";
const std::string CTemp::separator = "_";
int CTemp::nextUniqueId = 0;

// ����������� ��� ����������
CTemp::CTemp() {
	name = suffix + "_" + std::to_string( nextUniqueId );
}

// �����������, � ������� �� ������� ������
CTemp::CTemp( const Symbol::CSymbol* symbol ) {
	name = symbol->GetString() + separator + suffix + separator + std::to_string( nextUniqueId );
}