#pragma once
#include <iostream>

class test {
	private: 
		std::string value;

	public:
		test(std::string value) {
			this->value = value;
		}

		std::string getValue() {
			return value;
		}
};
