/*
* ????????? ????????? ????????? ??? ???????????? ????????
*/
#pragma once
#include <string>

// ?????????????
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