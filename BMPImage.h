#ifndef BMP_IMAGE_H
#define BMP_IMAGE_H

#define uint unsigned int
#define uchar unsigned char

#include <vector>

typedef struct BMPHeader
{
	uchar id[2];
	uint fileSize;
	uchar appSpec[2];
	uint pixelOffset;
} BMPHeader;

typedef struct DIBHeader
{
	uint DIBHeaderSize;
	uint width;
	uint height;
	uchar plateColorsCount;
	uchar bitsPerPixel;
	uint compression;
	uint dataSize;
	uint printWidth;
	uint printHeight;
	uint paletteColorsCount;
	uint importantColorsCount;

}DIBHeader;

typedef struct BMPFile
{
	BMPHeader bmpHeader;
	DIBHeader dipHeader;
	uchar* data;
}BMPFile;



class BMPImage
{
public:
	BMPImage(int width, int height);
	BMPImage(const char* path);
	~BMPImage();

	void RotateIamge();
	void ApplyGaussianBluring();

	void ExportToFile(const char * path);
	void ImportFromFile(const char * path);


private:
	int mWidth;
	int mHeight;
	unsigned char* data;
};

#endif