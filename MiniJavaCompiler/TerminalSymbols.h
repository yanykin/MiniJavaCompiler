/*
* Описывает некоторые примитивы для терминальных символов
*/
#pragma once
#include <string>

// Идентификатор
class CIdentifier
{
public:
	CIdentifier() {};
	std::string getString() {
		return identifier;
	}
private:
	std::string identifier;
};