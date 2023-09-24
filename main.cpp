#include "BMPImage.h"
#include <iostream>


int main()
{
	BMPImage bmim("C:\\Users\\User\\Downloads\\sample.bmp");

	std::cout << bmim.bmpFile->bmpHeader.id[0] << bmim.bmpFile->bmpHeader.id[1] << std::endl;

	bmim.FreeData();

	return 0;
}