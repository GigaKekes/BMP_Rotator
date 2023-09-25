#include "BMPImage.h"
#include <stdio.h>
#include <iostream>


int main()
{
	BMPImage bmim("C:\\Users\\User\\Desktop\\sampels\\sample2.bmp");

	std::cout << "Width: " << bmim.bmpFile->dibHeader.width << std::endl;
	std::cout << "Height: " << bmim.bmpFile->dibHeader.height << std::endl;
	std::cout << "Data size: " << bmim.bmpFile->dibHeader.dataSize << std::endl;
	std::cout << "bits per pixel: " << bmim.bmpFile->dibHeader.bitsPerPixel << std::endl;


	for (int i = 0; i < bmim.bmpFile->dibHeader.width* bmim.bmpFile->dibHeader.height; i++)
	{
		std::cout << (int)bmim.readableData[i][0] << ' ' << (int)bmim.readableData[i][1] << ' ' << (int)bmim.readableData[i][2] << std::endl;
	}

	bmim.FreeData();

	return 0;
}