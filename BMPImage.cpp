#include "BMPImage.h"
#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

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

#pragma region gaussian blur
vector<int> BMPImage::boxesForGauss(double sigma, int n)
{
	int wl = floor(sqrt((12 * sigma * sigma / n) + 1));
	
	if (wl % 2 == 0) 
		wl--;

	int wu = wl + 2;

	int m = round((12 * sigma * sigma - n * wl * wl - 4 * n * wl - 3 * n) / (-4 * wl - 4));

	vector<int> sizes;  
	for (int i = 0; i < n; i++) 
		sizes.push_back(i < m ? wl : wu);
	
	return sizes;
}
void BMPImage::boxBlurT(unsigned char** newReadableData, int r) 
{
	double iarr = (float)1 / (r + r + 1);

	int w = bmpFile->dibHeader.width;
	int h = bmpFile->dibHeader.height;

	for (int i = 0; i < w; i++) {
		int ti = i, li = ti, ri = ti + r * w;
		int fv0 = readableData[ti][0], fv1 = readableData[ti][1], fv2 = readableData[ti][3];
		int lv0 = readableData[ti + w - 1][0], lv1 = readableData[ti + w * (h - 1)][1], lv2 = readableData[ti + w * (h - 1)][2];
		int val0 = (r + 1) * fv0, val1 = (r + 1) * fv1, val2 = (r + 1) * fv2;


		for (int j = 0; j < r; j++)
		{
			val0 += readableData[ti + j * w][0];
			val1 += readableData[ti + j * w][1];
			val2 += readableData[ti + j * w][2];

		}
		for (int j = 0; j <= r; j++) 
		{ 

			val0 += readableData[ri][0] - fv0;
			val1 += readableData[ri][1] - fv1;
			val2 += readableData[ri][2] - fv2;

			newReadableData[ti][0] = round(val0 * iarr);
			newReadableData[ti][1] = round(val1 * iarr);
			newReadableData[ti][2] = round(val2 * iarr);

			ri += w; 
			ti += w; 
		}

		for (int j = r + 1; j < h - r; j++) 
		{ 
			val0 += readableData[ri][0] - readableData[li][0];
			val1 += readableData[ri][1] - readableData[li][1];
			val2 += readableData[ri][2] - readableData[li][2];

			newReadableData[ti][0] = round(val0 * iarr);
			newReadableData[ti][1] = round(val1 * iarr);
			newReadableData[ti][2] = round(val2 * iarr);
		
			li += w;
			ri += w;
			ti += w;
		}
		for (int j = h - r; j < h; j++) 
		{ 
			val0 += lv0 - readableData[li][0];
			val1 += lv1 - readableData[li][1];
			val2 += lv2 - readableData[li][2];

			newReadableData[ti][0] = round(val0 * iarr);
			newReadableData[ti][1] = round(val1 * iarr);
			newReadableData[ti][2] = round(val2 * iarr);
			
			li += w; 
			ti += w; 
		}
	}
}
void BMPImage::boxBlurH(unsigned char** newReadableData, int r) {
	float iarr = (float)1 / (r + r + 1);
	int w = bmpFile->dibHeader.width;
	int h = bmpFile->dibHeader.height;


	for (int i = 0; i < h; i++) {
		int ti = i * w, li = ti, ri = ti + r;
		char fv0 = readableData[ti][0], fv1 = readableData[ti][1], fv2 = readableData[ti][2];
		char lv0 = readableData[ti + w - 1][0], lv1 = readableData[ti + w - 1][1], lv2 = readableData[ti + w - 1][2];
		int val0 = (r + 1) * fv0, val1 = (r + 1) * fv1, val2 = (r + 1) * fv2;


		for (int j = 0; j < r; j++)
		{
			val0 += readableData[ti + j][0];
			val1 += readableData[ti + j][1];
			val2 += readableData[ti + j][2];

		}
		for (int j = 0; j <= r; j++)
		{
			val0 += readableData[ri][0] - fv0;
			val1 += readableData[ri][1] - fv1;
			val2 += readableData[ri][2] - fv2;
			ri++;

			newReadableData[ti][0] = round(val0 * iarr);
			newReadableData[ti][1] = round(val1 * iarr);
			newReadableData[ti][2] = round(val2 * iarr);
			ti++;
		}
		for (int j = r + 1; j < w - r; j++)
		{
			val0 += readableData[ri][0] - readableData[li][0];
			val1 += readableData[ri][1] - readableData[li][1];
			val2 += readableData[ri][2] - readableData[li][2];
			li++;
			ri++;
			newReadableData[ti][0] = round(val0 * iarr);
			newReadableData[ti][1] = round(val1 * iarr);
			newReadableData[ti][2] = round(val2 * iarr);
			ti++;
		}
		for (int j = w - r; j < w; j++)
		{
			val0 += lv0 - readableData[li][0];
			val1 += lv1 - readableData[li][1];
			val2 += lv2 - readableData[li][2];
			li++;
			newReadableData[ti][0] = round(val0 * iarr);
			newReadableData[ti][1] = round(val1 * iarr);
			newReadableData[ti][2] = round(val2 * iarr);
			ti++;
			
		}
	}
}
void BMPImage::boxBlur(unsigned char** newReadableData, int r) {
	for (int i = 0; i < bmpFile->dibHeader.width * bmpFile->dibHeader.height; i++)
	{
		newReadableData[i][0] = readableData[i][0];
		newReadableData[i][1] = readableData[i][1];
		newReadableData[i][2] = readableData[i][2];
	}
	boxBlurH(newReadableData, r);
	boxBlurT(newReadableData, r);
}

void BMPImage::ApplyGaussianBluring(int r) {

	unsigned char** newReadableData = (unsigned char**)malloc(bmpFile->dibHeader.height * bmpFile->dibHeader.width * sizeof(*newReadableData));
	for (int i = 0; i < bmpFile->dibHeader.height * bmpFile->dibHeader.width; i++) {
		newReadableData[i] = (unsigned char*)malloc(3 * sizeof(newReadableData[0]));
	}

	vector<int> bxs = boxesForGauss(r, 3);
	boxBlur(newReadableData, (bxs[0] - 1) / 2);
	boxBlur(newReadableData, (bxs[1] - 1) / 2);
	boxBlur(newReadableData, (bxs[2] - 1) / 2);

	unsigned char** temp = readableData;
	readableData = newReadableData;

	for (int i = 0; i < bmpFile->dibHeader.width * bmpFile->dibHeader.height; i++)
	{
		free(temp[i]);
	}
	free(temp);
}

#pragma endregion

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

