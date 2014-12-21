#pragma once
#include <string>

namespace Temp {
	class CLabel {
	public:
		// Создать метку с уникальным именем
		CLabel();
		// Создать метку с заданным именем
		explicit CLabel();

		const std::string& GetName() const { return name; }

	private:
		std::string name;
		static int nextUniqueId;
	};
}