#include <iostream>
#include "NVector.h"

int main()
{
	NVector vec_1 = { 1, 2, 3, 4 };
	NVector vec_3 = { 3, 4, 2, 5 };
	NVector vec_2(2);
	NVector vec_4(2);
	vec_2[0] = 2;
	vec_2[1] = 4;
	NVector vec_5 = vec_1 + vec_3;
	std::cout << vec_5 << std::endl;
	std::cout << vec_1.length() << std::endl;
	std::cout << vec_1 << std::endl;
	vec_1.normalize();
	std::cout << vec_1 << std::endl;
	std::cout << vec_1.length() << std::endl;
}