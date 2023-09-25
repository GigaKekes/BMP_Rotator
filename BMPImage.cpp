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
	if (!bmpFile)
	{
		std::cout << "There is no data imported" << std::endl;
		exit(0);
	}
	
	FILE* file;
	fopen_s(&file, path, "w");
	if (!file)
	{
		std::cout << "Error. Failed to write into " << path << std::endl;
		exit(0);
	}

	fwrite(&bmpFile->bmpHeader, sizeof(struct BMPHeader), 1, file);
	fwrite(&bmpFile->dibHeader, sizeof(struct DIBHeader), 1, file);
	fseek(file, bmpFile->bmpHeader.pixelOffset, SEEK_SET);
	fwrite(bmpFile->data, bmpFile->dibHeader.dataSize, 1, file);
	fclose(file);


} 

void BMPImage::ImportFromFile(const char* path)
{
	FILE* file;
	fopen_s(&file, path, "r");

	if (!file)
	{
		std::cout << "Error. Failed to read " << path << std::endl;
		exit(0);
	}

	
	bmpFile = (BMPFile*)malloc(sizeof(BMPFile));
	fread(&bmpFile->bmpHeader, sizeof(BMPHeader), 1, file);
	fread(&bmpFile->dibHeader, sizeof(DIBHeader), 1, file);

	bmpFile->data = (unsigned char*)malloc(bmpFile->dibHeader.dataSize);

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
