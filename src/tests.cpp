#include <iostream>





int main()
{
	unsigned short b2 = 0x0f0f;

	std::cout << "b2 == " << b2 << std::endl;

	unsigned short bb2 = ( b2 & 0x00ff);

	std::cout << "bb2 == " << bb2 << std::endl;

}