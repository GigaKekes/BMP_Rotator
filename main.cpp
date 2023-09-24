#include "BMPImage.h"
#include <stdio.h>
#include <iostream>


int main()
{
	BMPImage bmim("C:\\Users\\User\\Downloads\\sample.bmp");

	std::cout << bmim.bmpFile->dibHeader.DIBHeaderSize << std::endl;
	std::cout << bmim.bmpFile->dibHeader.width << std::endl;
	std::cout << bmim.bmpFile->dibHeader.height << std::endl;
	std::cout << bmim.bmpFile->dibHeader.dataSize << std::endl;


	/*for (int i = 0; i < bmim.bmpFile->dibHeader.dataSize; i++)
	{
		if (i % 16 == 0)
		{
			printf("\n%04x: ", i);
		}
		printf("%02x ", bmim.bmpFile->data[i]);
	}*/


	bmim.FreeData();

	return 0;
}