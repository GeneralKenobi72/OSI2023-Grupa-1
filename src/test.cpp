#include "test.h"
#include <iostream>

int main() {
	test t1 = test("kevin panter, probace preko jabuselea...\n\n\n\n\n\nOAAAAAAA KEVIN PANTER\n\nvreme nije isteklo");

	std::cout << t1.getValue();
	return 0;
}
