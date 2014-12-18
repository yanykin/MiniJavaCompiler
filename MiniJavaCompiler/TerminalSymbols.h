/*
* Описывает некоторые примитивы для терминальных символов
*/
#pragma once
#include <string>

// Идентификатор
class CIdentifier
{
public:
	CIdentifier(const char* _identifier): identifier(_identifier) {};
	std::string getString() {
		return identifier;
	}
private:
	std::string identifier;
};