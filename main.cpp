#include "BMPImage.h"
#include <stdio.h>
#include <iostream>


int main()
{
	BMPImage bmim("C:\\Users\\User\\Desktop\\sampels\\sample5.bmp");

	std::cout << "Width: " << bmim.bmpFile->dibHeader.width << std::endl;
	std::cout << "Height: " << bmim.bmpFile->dibHeader.height << std::endl;
	std::cout << "Data size: " << bmim.bmpFile->dibHeader.dataSize << std::endl;
	std::cout << "bits per pixel: " << bmim.bmpFile->dibHeader.bitsPerPixel << std::endl;


	/*for (int i = 0; i < bmim.bmpFile->dibHeader.dataSize; i++)
	{
		if (i % 16 == 0)
		{
			printf("\n%04x: ", i);
		}
		printf("%02x ", bmim.bmpFile->data[i]);
	}*/
	bmim.ExportToFile("C:\\Users\\User\\Desktop\\sampels\\sol5.bmp");

	bmim.FreeData();

	return 0;
}