#include "Utils.h"
#include <iostream>

void Utils::log(std::string message) {
#ifdef _DEBUG
	std::cout << message << std::endl;
#endif
}