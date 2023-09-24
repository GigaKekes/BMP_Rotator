#include "BMPImage.h"
#include <iostream>

BMPImage::BMPImage(const char* path)
{
	ImportFromFile(path);
}

BMPImage::~BMPImage()
{
}


void BMPImage::RotateIamge()
{
}

void BMPImage::ApplyGaussianBluring()
{
}

void BMPImage::ExportToFile(const char* path)
{
}

void BMPImage::ImportFromFile(const char* path)
{
	FILE* file;
	fopen_s(&file, path, "r");

	if (!file)
	{
		std::cout << "File opening error " << path << std::endl;
		exit(0);
	}

	
	bmpFile = (BMPFile*)malloc(sizeof(BMPFile));
	fread(&bmpFile->bmpHeader, sizeof(BMPHeader), 1, file);
	fread(&bmpFile->dibHeader, sizeof(DIBHeader), 1, file);

	bmpFile->data = (UCHAR*)malloc(bmpFile->dibHeader.dataSize);

	fseek(file, bmpFile->bmpHeader.pixelOffset, SEEK_SET);
	fread(bmpFile->data, bmpFile->dibHeader.dataSize, 1, file);
	fclose(file);

	mdata = bmpFile->data;

}

void BMPImage::FreeData()
{
	if (bmpFile)
	{
		if (bmpFile->data)
		{
			free(bmpFile->data);
		}
		free(bmpFile);
	}
}
