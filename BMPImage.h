#ifndef BMP_IMAGE_H
#define BMP_IMAGE_H

#define UINT unsigned int
#define UCHAR unsigned char

#pragma pack(1)
typedef struct BMPHeader
{
	UCHAR id[2];
	UINT fileSize;
	UCHAR appSpec[2];
	UINT pixelOffset;
} BMPHeader;

typedef struct DIBHeader
{
	UINT DIBHeaderSize;
	UINT width;
	UINT height;
	unsigned short plateColorsCount;
	unsigned short bitsPerPixel;
	UINT compression;
	UINT dataSize;
	UINT printWidth;
	UINT printHeight;
	UINT paletteColorsCount;
	UINT importantColorsCount;

}DIBHeader;

typedef struct BMPFile
{
	BMPHeader bmpHeader;
	DIBHeader dibHeader;
	UCHAR* data;
}BMPFile;
#pragma pop


class BMPImage
{
public:
	BMPFile * bmpFile;


	BMPImage(int width, int height);
	BMPImage(const char* path);
	~BMPImage();

	void RotateIamge();
	void ApplyGaussianBluring();

	void ExportToFile(const char * path);
	void ImportFromFile(const char * path);

	void FreeData();

private:
	int mWidth;
	int mHeight;
	unsigned char* mdata;
};

#endif