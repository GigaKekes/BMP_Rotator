#include "BMPImage.h"
#include <iostream>

#define TABLE_SIZE 5


BMPImage::BMPImage(const char* path)
{
	ImportFromFile(path);
}

BMPImage::~BMPImage()
{
	if (readableData)
	{
		for (int i = 0; i < bmpFile->dibHeader.width * bmpFile->dibHeader.height; i++)
		{
			free(readableData[i]);
		}
		free(readableData);
	}

	free(bmpFile->garbage);
	free(bmpFile);
}

void BMPImage::RotateImage(int direction)
{
	if (!readableData)
	{
		std::cout << "There is no data inputed to perform the rotation" << std::endl;
		exit(0);
	}
	
	unsigned char** newReadableData = (unsigned char**)malloc(bmpFile->dibHeader.height * bmpFile->dibHeader.width * sizeof(*newReadableData));
	for (int i = 0; i < bmpFile->dibHeader.height * bmpFile->dibHeader.width; i++) {
		newReadableData[i] = (unsigned char*)malloc(3 * sizeof(newReadableData[0]));
	}
	int newWidth = bmpFile->dibHeader.height;
	int newHeight = bmpFile->dibHeader.width;

	switch (direction)
	{
		case CLOCKWISE_ROTATION:
			for (int i = 0; i < newHeight; i++)
			{
				for (int j = 0; j < newWidth; j++)
				{
					newReadableData[i * newWidth + j][0] = readableData[j * bmpFile->dibHeader.width + (bmpFile->dibHeader.width - i - 1)][0];
					newReadableData[i * newWidth + j][1] = readableData[j * bmpFile->dibHeader.width + (bmpFile->dibHeader.width - i - 1)][1];
					newReadableData[i * newWidth + j][2] = readableData[j * bmpFile->dibHeader.width + (bmpFile->dibHeader.width - i - 1)][2];
				}
			}
			break;
		case CONTER_CLOCKWISE_ROTATION:
			for (int i = 0; i < newHeight; i++)
			{
				for (int j = 0; j < newWidth; j++)
				{
					newReadableData[i * newWidth + j][0] = readableData[(bmpFile->dibHeader.height - j - 1) * bmpFile->dibHeader.width + i][0];
					newReadableData[i * newWidth + j][1] = readableData[(bmpFile->dibHeader.height - j - 1) * bmpFile->dibHeader.width + i][1];
					newReadableData[i * newWidth + j][2] = readableData[(bmpFile->dibHeader.height - j - 1) * bmpFile->dibHeader.width + i][2];

				}
			}
			break;
	}
	bmpFile->dibHeader.height = newHeight;
	bmpFile->dibHeader.width = newWidth; 
	
	unsigned char** temp = readableData;
	readableData = newReadableData;

	for (int i = 0; i < bmpFile->dibHeader.width * bmpFile->dibHeader.height; i++)
	{
		free(temp[i]);
	}
	free(temp);
	
	
}

void BMPImage::ApplyGaussianBluring()
{
	float blurTable[TABLE_SIZE][TABLE_SIZE] = {
		{0.0030, 0.0133, 0.0219, 0.0133, 0.0030},
		{0.0133, 0.0596, 0.0983, 0.0596, 0.0133},
		{0.0219, 0.0983, 0.1621, 0.0983, 0.0219},
		{0.0133, 0.0596, 0.0983, 0.0596, 0.0133},
		{0.0030, 0.0133, 0.0219, 0.0133, 0.0030}
	};

	const int width = bmpFile->dibHeader.width;
	const int height = bmpFile->dibHeader.height;
	
	unsigned char** newReadableData = (unsigned char**)malloc(bmpFile->dibHeader.height * bmpFile->dibHeader.width * sizeof(*newReadableData));
	for (int i = 0; i < bmpFile->dibHeader.height * bmpFile->dibHeader.width; i++) {
		newReadableData[i] = (unsigned char*)malloc(3 * sizeof(newReadableData[0]));
	}

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			float sumr = 0.0;
			float sumg = 0.0;
			float sumb = 0.0;
			for (int i = 0; i < TABLE_SIZE; i++) {
				for (int j = 0; j < TABLE_SIZE; j++) {
					int xn = x + i - TABLE_SIZE / 2;
					int yn = y + j - TABLE_SIZE / 2;
					if (xn >= 0 && xn < width && yn >= 0 && yn < height) {
						sumr += readableData[yn * width + xn][0] * blurTable[i][j];
						sumg += readableData[yn * width + xn][1] * blurTable[i][j];
						sumb += readableData[yn * width + xn][2] * blurTable[i][j];
					}
				}
			}
			newReadableData[y * width + x][0] = (int)sumr;
			newReadableData[y * width + x][1] = (int)sumg;
			newReadableData[y * width + x][2] = (int)sumb;
		}
	}

	unsigned char** temp = readableData;
	readableData = newReadableData;

	for (int i = 0; i < bmpFile->dibHeader.width * bmpFile->dibHeader.height; i++)
	{
		free(temp[i]);
	}
	free(temp);

}

void BMPImage::ExportToFile(const char* path)
{
	if (!bmpFile)
	{
		std::cout << "There is no data imported" << std::endl;
		exit(0);
	}

	FILE* file;
	fopen_s(&file, path, "wb");
	if (!file)
	{
		std::cout << "Error. Failed to write into " << path << std::endl;
		exit(0);
	}

	fwrite(&bmpFile->bmpHeader, sizeof(struct BMPHeader), 1, file);
	fwrite(&bmpFile->dibHeader, sizeof(struct DIBHeader), 1, file);
	fwrite(&bmpFile->garbage, sizeof(bmpFile->garbage), 1, file);
	fseek(file, bmpFile->bmpHeader.pixelOffset, SEEK_SET);
	
	char c = 0;
	int bytesPerPixel = bmpFile->dibHeader.bitsPerPixel / 8;
	int rowSize = bytesPerPixel * bmpFile->dibHeader.width;
	int rowPadding = (4 - (rowSize % 4)) % 4;
	

	for (int i = 0; i < bmpFile->dibHeader.height; i++)
	{
		for (int j = 0; j < bmpFile->dibHeader.width; j++)
		{
			fwrite(&readableData[i * bmpFile->dibHeader.width + j][2], sizeof(char), 1, file);
			fwrite(&readableData[i * bmpFile->dibHeader.width + j][1], sizeof(char), 1, file);
			fwrite(&readableData[i * bmpFile->dibHeader.width + j][0], sizeof(char), 1, file);
		}
		for (int k = rowPadding; k != 0; k--)
		{
			fwrite(&c, sizeof(char), 1, file);
		}
	}

	fclose(file);

} 

void BMPImage::ImportFromFile(const char* path)
{
	FILE* file;
	fopen_s(&file, path, "rb");

	if (!file)
	{
		std::cout << "Error. Failed to read " << path << std::endl;
		exit(0);
	}

	
	bmpFile = (BMPFile*)malloc(sizeof(BMPFile));
	fread(&bmpFile->bmpHeader, sizeof(BMPHeader), 1, file);
	fread(&bmpFile->dibHeader, sizeof(DIBHeader), 1, file);
	bmpFile->garbage = (unsigned char*)malloc(bmpFile->bmpHeader.pixelOffset - 54);
	fread(&bmpFile->garbage, sizeof(bmpFile->bmpHeader.pixelOffset - 54), 1, file);

	int bytesPerPixel = bmpFile->dibHeader.bitsPerPixel / 8;
	int rowSize = bytesPerPixel * bmpFile->dibHeader.width;
	int rowPadding = (4 - (rowSize % 4)) % 4;

	unsigned char* row = (unsigned char*)malloc(rowSize + rowPadding);

	

	fseek(file, bmpFile->bmpHeader.pixelOffset, SEEK_SET);

	if (bytesPerPixel == 3)
	{
		readableData = (unsigned char**)malloc(bmpFile->dibHeader.height * bmpFile->dibHeader.width * sizeof(*readableData));
		for (int i = 0; i < bmpFile->dibHeader.height * bmpFile->dibHeader.width; i++)
		{
			readableData[i] = (unsigned char*)malloc(3 * sizeof(unsigned char));
		}

		for(int i = 0; i < bmpFile->dibHeader.height; i++)
		{
			fread(row, rowSize + rowPadding, 1, file);
			for (int j = 0; j < rowSize; j += bytesPerPixel)
			{
				readableData[i * bmpFile->dibHeader.width + j / bytesPerPixel][0] = row[j + 2];
				readableData[i * bmpFile->dibHeader.width + j / bytesPerPixel][1] = row[j + 1];
				readableData[i * bmpFile->dibHeader.width + j / bytesPerPixel][2] = row[j];
			}
		}
	}

	free(row);
	fclose(file);
}

void BMPImage::FreeData()
{
	
}

