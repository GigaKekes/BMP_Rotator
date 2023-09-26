#include "BMPImage.h"
#include <iostream>

BMPImage::BMPImage(const char* path)
{
	ImportFromFile(path);
}

BMPImage::~BMPImage()
{
}


void BMPImage::RotateImage()
{
	if (!readableData)
	{
		std::cout << "There is no data inputed to perform the rotation" << std::endl;
		exit(0);
	}
	
	unsigned char** newReadableData = (unsigned char**)malloc(mHeight * mWidth * sizeof(*newReadableData));
	for (int i = 0; i < mHeight * mWidth; i++) {
		newReadableData[i] = (unsigned char*)malloc(3 * sizeof(newReadableData[0]));
	}
	int newWidth = mHeight;
	int newHeight = mWidth;

	for (int i = 0; i < newHeight; i++)
	{ 
		for (int j = 0; j < newWidth; j++)
		{
			newReadableData[i * newWidth + j][0] = readableData[j * mWidth + (mWidth - i - 1)][0];
			newReadableData[i * newWidth + j][1] = readableData[j * mWidth + (mWidth - i - 1)][1];
			newReadableData[i * newWidth + j][2] = readableData[j * mWidth + (mWidth - i - 1)][2];
		}
	}
	unsigned char** temp = readableData;
	readableData = newReadableData;

	for (int i = 0; i < mWidth * mHeight; i++)
	{
		free(temp[i]);
	}
	free(temp);

	bmpFile->dibHeader.height = newHeight; mWidth = newHeight;
	bmpFile->dibHeader.width = newWidth; mHeight = newWidth;
	
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

	mWidth = bmpFile->dibHeader.width;
	mHeight = bmpFile->dibHeader.height;


	int bytesPerPixel = bmpFile->dibHeader.bitsPerPixel / 8;
	int rowSize = bytesPerPixel * mWidth;
	int rowPadding = (4 - (rowSize % 4)) % 4;
	int rowsLeft = 0;

	unsigned char* row = (unsigned char*)malloc(rowSize + rowPadding);

	readableData = (unsigned char**)malloc(mHeight * mWidth * sizeof(*readableData));
	for (int i = 0; i < mHeight * mWidth; i++) {
		readableData[i] = (unsigned char*)malloc(3 * sizeof(readableData[0]));
	}

	fseek(file, bmpFile->bmpHeader.pixelOffset, SEEK_SET);

	while (rowsLeft < mHeight)
	{
		fread(row, rowSize + rowPadding, 1, file);
		for (int i = 0; i < rowSize; i += bytesPerPixel)
		{
			readableData[rowsLeft * mWidth + i / bytesPerPixel][0] = row[i+2];
			readableData[rowsLeft * mWidth + i / bytesPerPixel][1] = row[i+1];
			readableData[rowsLeft * mWidth + i / bytesPerPixel][2] = row[i];
		}
		rowsLeft++;
	}
	free(row);

	fclose(file);
}

void BMPImage::FreeData()
{
	if (readableData)
	{
		for (int i = 0; i < mWidth * mHeight; i++)
		{
			free(readableData[i]);
		}
		free(readableData);
	}
}