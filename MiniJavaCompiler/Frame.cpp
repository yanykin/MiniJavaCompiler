#include "Frame.h"

using namespace Frame;

void CFrame::AddFormal( const Symbol::CSymbol* name ) {
	// TODO: ������� ���������� IAccess � �������� ���� ����
	formalCount += 1;
}

void CFrame::AddLocal( const Symbol::CSymbol* name ) {
	// TODO: ������� ���������� IAccess � �������� ���� ����
}

const IAccess* CFrame::FindLocalOrFormal( const Symbol::CSymbol* name ) const {
	// ������� ���� ����� ��������� ����������
	auto itLocal = localVariables.find( name );
	if ( itLocal != localVariables.end() ) {
		return itLocal->second;
	}

	// ����� �������� ����� ���������� ����������
	auto itFormal = methodFormals.find( name );
	if ( itFormal != methodFormals.end() ) {
		return itFormal->second;
	}

	// ���� �� ����� - ���������� ������
	return NULL;
}
