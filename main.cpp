#include "BMPImage.h"
#include <stdio.h>
#include <iostream>

void space();
void printRGB(BMPImage bmim);
void printEssential(BMPImage bmim);
void printDataBytes(BMPImage bmim);
void printHeader(BMPImage bmim);

int main()
{
	BMPImage b("C:\\Users\\User\\Desktop\\sampels\\sample10.bmp");
	b.ExportToFile("C:\\Users\\User\\Desktop\\sampels\\sol10.bmp");

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
		std::cout << '(' << i % bmim.bmpFile->dibHeader.width << ';' << i / bmim.bmpFile->dibHeader.width << ") "
			<< (int)bmim.readableData[i][0] << ' ' << (int)bmim.readableData[i][1] << " "
			<< (int)bmim.readableData[i][2] << std::endl;
	}
}

void printHeader(BMPImage bmim)
{

	std::cout << "Offset: " << bmim.bmpFile->bmpHeader.pixelOffset << std::endl;
	std::cout << "Width: " << bmim.bmpFile->dibHeader.width << std::endl;
	std::cout << "Height: " << bmim.bmpFile->dibHeader.height << std::endl;
	std::cout << "planes: " << bmim.bmpFile->dibHeader.planes << std::endl;
	std::cout << "bitsPerPixel: " << bmim.bmpFile->dibHeader.bitsPerPixel << std::endl;
	std::cout << "compression: " << bmim.bmpFile->dibHeader.compression << std::endl;
	std::cout << "dataSize: " << bmim.bmpFile->dibHeader.dataSize << std::endl;
	std::cout << "pWidth: " << bmim.bmpFile->dibHeader.pWidth << std::endl;
	std::cout << "pHeight: " << bmim.bmpFile->dibHeader.pHeight << std::endl;
	std::cout << "colorsUsed: " << bmim.bmpFile->dibHeader.colorsUsed << std::endl;
	std::cout << "colors in color table: " << bmim.bmpFile->dibHeader.colorsUsed << std::endl;
	std::cout << "importantColors: " << bmim.bmpFile->dibHeader.importantColors << std::endl;

}