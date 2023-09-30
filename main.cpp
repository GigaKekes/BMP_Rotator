#include "BMPImage.h"
#include <iostream>
#include <string>

using namespace std;

void space();
void printRGB(BMPImage bmim);
void printEssential(BMPImage bmim);
void printHeader(BMPImage bmim);

int main()
{
	string importPath;
	cout << "Enter a path to the file: ";
	getline(cin, importPath);

	const char* nimportPath = importPath.c_str();
	BMPImage b(nimportPath);

	cout << "Image imported succsessfuly" << endl;


	int option = 0;
	while(option != 5)
	{
		cout << "1. Rotate image clockwise\n2. Rotate image conter clockwise\n3. Apply Gaussian bluring\n4. Export to file\n5. Quit" << endl;
		cin >> option;

		switch (option)
		{
			case 1: 
			{
				b.RotateImage(CLOCKWISE_ROTATION);
				cout << "Image rotated clockwise succsessfuly" << endl;
				break;
			}

			case 2: 
			{
				b.RotateImage(CONTER_CLOCKWISE_ROTATION);
				cout << "Image rotated conter clockwise succsessfuly" << endl;
				break;
			}

			case 3: 
			{
				b.ApplyGaussianBluring();
				cout << "Gaussian bluring applyed succsessfuly" << endl;
				break;
			}

			case 4:
			{
				string exportPath;
				cout << "Enter a path to the file: ";

				cin.ignore();
				getline(cin, exportPath);

				const char* nExportPath = exportPath.c_str();

				b.ExportToFile(nExportPath);

				cout << "Image Exported succsessfuly" << endl;
				break;
			}
			
			case 5:
			{
				cout << "Quitting" << endl;
				break;
			}
			
			default:
				cout << "No such command" << endl;
		}
	}



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