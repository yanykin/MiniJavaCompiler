#include "Frame.h"

using namespace Frame;

void CFrame::AddFormal( const Symbol::CSymbol* name ) {
	// TODO: создать переменную IAccess и положить куда надо
	formalCount += 1;
}

void CFrame::AddLocal( const Symbol::CSymbol* name ) {
	// TODO: создать переменную IAccess и положить куда надо
}

const IAccess* CFrame::FindLocalOrFormal( const Symbol::CSymbol* name ) const {
	// Сначала ищем среди локальных переменных
	auto itLocal = localVariables.find( name );
	if ( itLocal != localVariables.end() ) {
		return itLocal->second;
	}

	// Потом пытаемся среди переданных аргументов
	auto itFormal = methodFormals.find( name );
	if ( itFormal != methodFormals.end() ) {
		return itFormal->second;
	}

	// Если не нашли - возвращаем ничего
	return NULL;
}
