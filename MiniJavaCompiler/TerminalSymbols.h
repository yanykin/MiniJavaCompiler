/*
* ��������� ��������� ��������� ��� ������������ ��������
*/
#pragma once
#include <string>

// �������������
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