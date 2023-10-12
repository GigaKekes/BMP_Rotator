#include "BMPImage.h"
#include <iostream>
#include <string>
#include <chrono>

using namespace std;

void space();
void printRGB(BMPImage bmim);
void printEssential(BMPImage bmim);
void printHeader(BMPImage bmim);
void startDefaultUI();

int main()
{
	startDefaultUI();
}

void startDefaultUI()
{
	string importPath;
	cout << "Enter a path to the file: ";
	getline(cin, importPath);

	const char* nimportPath = importPath.c_str();
	BMPImage b(nimportPath);

	cout << "Image imported succsessfuly" << endl;


	int option = 0;
	while (option != 5)
	{
		cout << "1. Rotate image clockwise\n2. Rotate image conter clockwise\n3. Apply Gaussian bluring\n4. Export to file\n5. Quit" << endl;
		cin >> option;

		switch (option)
		{
		case 1:
		{
			auto start_time = std::chrono::steady_clock::now();
			b.RotateImage(CLOCKWISE_ROTATION);
			auto end_time = std::chrono::steady_clock::now();
			auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
			cout << "Image rotated clockwise succsessfuly in " << elapsed_ms.count() << "ms" << endl;
			break;
		}

		case 2:
		{
			auto start_time = std::chrono::steady_clock::now();
			b.RotateImage(CONTER_CLOCKWISE_ROTATION);
			auto end_time = std::chrono::steady_clock::now();
			auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
			cout << "Image rotated conter clockwise succsessfuly in " << elapsed_ms.count() << "ms" << endl;
			break;
		}

		case 3:
		{
			int r = 0;
			cout << "Enter radius: ";
			cin >> r;

			auto start_time = std::chrono::steady_clock::now();
			b.ApplyGaussianBluring(r);
			auto end_time = std::chrono::steady_clock::now();
			auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);

			cout << "Gaussian bluring applyed succsessfuly in " << elapsed_ms.count() << "ms" << endl;
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
	std::cout << "Width: " << bmim.bmpHeader.width << std::endl;
	std::cout << "Height: " << bmim.bmpHeader.height << std::endl;
	std::cout << "Data size: " << bmim.bmpHeader.dataSize << std::endl;
	std::cout << "bits per pixel: " << bmim.bmpHeader.bitsPerPixel << std::endl;

}

void printRGB(BMPImage bmim)
{
	for (int i = 0; i < bmim.bmpHeader.width * bmim.bmpHeader.height; i++)
	{
		std::cout << '(' << i % bmim.bmpHeader.width << ';' << i / bmim.bmpHeader.width << ") "
			<< (int)bmim.readableData[i][0] << ' ' << (int)bmim.readableData[i][1] << " "
			<< (int)bmim.readableData[i][2] << std::endl;
	}
}

void printHeader(BMPImage bmim)
{

	std::cout << "Offset: " << bmim.bmpHeader.pixelOffset << std::endl;
	std::cout << "Width: " << bmim.bmpHeader.width << std::endl;
	std::cout << "Height: " << bmim.bmpHeader.height << std::endl;
	std::cout << "planes: " << bmim.bmpHeader.planes << std::endl;
	std::cout << "bitsPerPixel: " << bmim.bmpHeader.bitsPerPixel << std::endl;
	std::cout << "compression: " << bmim.bmpHeader.compression << std::endl;
	std::cout << "dataSize: " << bmim.bmpHeader.dataSize << std::endl;
	std::cout << "pWidth: " << bmim.bmpHeader.pWidth << std::endl;
	std::cout << "pHeight: " << bmim.bmpHeader.pHeight << std::endl;
	std::cout << "colorsUsed: " << bmim.bmpHeader.colorsUsed << std::endl;
	std::cout << "colors in color table: " << bmim.bmpHeader.colorsUsed << std::endl;
	std::cout << "importantColors: " << bmim.bmpHeader.importantColors << std::endl;

}