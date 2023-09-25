#ifndef BMP_IMAGE_H
#define BMP_IMAGE_H

#include <stdint.h>

#pragma pack(1)
typedef struct BMPHeader
{
	uint16_t type;           // Magic identifier "BM" (0x424D)
	uint32_t file_size;      // File size in bytes
	uint16_t reserved1;      
	uint16_t reserved2;      
	uint32_t pixelOffset;	 // Offset to the start of pixel data
} BMPHeader;

typedef struct DIBHeader
{
	uint32_t header_size;    // Size of the header (40 bytes)
	int32_t width;           // Image width in pixels
	int32_t height;          // Image height in pixels
	uint16_t planes;         // Number of color planes (1)
	uint16_t bitsPerPixel;	 // Bits per pixel (e.g., 24 for RGB)
	uint32_t compression;    // Compression method (0 for no compression)
	uint32_t dataSize;       // Image size in bytes (can be 0 for no compression)
	int32_t pWidth;			 // Pixels per meter in X direction (can be 0)
	int32_t pHeight;		 // Pixels per meter in Y direction (can be 0)
	uint32_t colorsUsed;    // Number of colors used (0 for full color)
	uint32_t importantColors; // Number of important colors (0 for all)

}DIBHeader;

typedef struct BMPFile
{
	BMPHeader bmpHeader;
	DIBHeader dibHeader;
	unsigned char* data;
}BMPFile;
#pragma pop


class BMPImage
{
public:
	BMPFile * bmpFile;

	BMPImage(int width, int height);
	BMPImage(const char* path);
	~BMPImage();

	void RotateImage();
	void ApplyGaussianBluring();

	void ExportToFile(const char * path);
	void ImportFromFile(const char * path);

	void FreeData();
	unsigned char** readableData;

private:
	int mWidth;
	int mHeight;
};

#endif