#pragma once
#include <iostream>
class Test
{
public:
	int Val = 0;
	Test() {
		std::cout << "Test object created" << std::endl;
	}

	~Test() {
		std::cout << "Test object destroyed" << std::endl;
	}
};

