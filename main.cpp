#include "BMPImage.h"
#include <stdio.h>
#include <iostream>

void space();
void printRGB(BMPImage bmim);
void printEssential(BMPImage bmim);
void printDataBytes(BMPImage bmim);

int main()
{
	BMPImage bmim("C:\\Users\\User\\Desktop\\sampels\\sample2.bmp");

	printEssential(bmim);
	space();
	printRGB(bmim);

	bmim.FreeData();
	return 0;
}

void space()
{
	std::cout << '\n' << std::endl;
}

void printEssential(BMPImage bmim)
{
	std::cout << "Width: " << bmim.bmpFile->dibHeader.width << std::endl;
	std::cout << "Height: " << bmim.bmpFile->dibHeader.height << std::endl;
	std::cout << "Data size: " << bmim.bmpFile->dibHeader.dataSize << std::endl;
	std::cout << "bits per pixel: " << bmim.bmpFile->dibHeader.bitsPerPixel << std::endl;

}

void printRGB(BMPImage bmim)
{
	for (int i = 0; i < bmim.bmpFile->dibHeader.width * bmim.bmpFile->dibHeader.height; i++)
	{
		std::cout << '(' << i / bmim.bmpFile->dibHeader.height << ';' << i % bmim.bmpFile->dibHeader.width << ") "
			<< (int)bmim.readableData[i][0] << ' ' << (int)bmim.readableData[i][1] << " "
			<< (int)bmim.readableData[i][2] << std::endl;
	}
}

void printDataBytes(BMPImage bmim)
{
	for (int i = 0; i < bmim.bmpFile->dibHeader.dataSize; i++)
	{
		if (i % 16 == 0)
		{
			printf("\n%04x: ", i);
		}
		printf("%02x ", bmim.bmpFile->data[i]);
	}
}