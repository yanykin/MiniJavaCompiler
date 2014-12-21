#pragma once
#include <string>

namespace Temp {
	class CLabel {
	public:
		// ������� ����� � ���������� ������
		CLabel();
		// ������� ����� � �������� ������
		explicit CLabel();

		const std::string& GetName() const { return name; }

	private:
		std::string name;
		static int nextUniqueId;
	};
}