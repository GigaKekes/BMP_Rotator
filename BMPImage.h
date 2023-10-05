#ifndef BMP_IMAGE_H
#define BMP_IMAGE_H

#define CLOCKWISE_ROTATION 0
#define CONTER_CLOCKWISE_ROTATION 1

#include <stdint.h>
#include <vector>

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
	uint16_t bitsPerPixel;	 // Bits per pixel (e.g., 24 for RGB and 32 for ARGB)
	uint32_t compression;    // Compression method (0 for no compression)
	uint32_t dataSize;       // Image size in bytes 
	int32_t pWidth;			 // Pixels per meter in X direction
	int32_t pHeight;		 // Pixels per meter in Y direction
	uint32_t colorsUsed;    // Number of colors used
	uint32_t importantColors; // Number of important colors

}DIBHeader;


typedef struct BMPFile
{
	BMPHeader bmpHeader;
	DIBHeader dibHeader;
	unsigned char* garbage;
}BMPFile;
#pragma pop


class BMPImage
{
public:
	BMPFile * bmpFile;
	unsigned char** readableData;

	BMPImage(const char* path);
	~BMPImage();

	void RotateImage(int direction);
	void ApplyGaussianBluring(int r);

	void ExportToFile(const char * path);
	void ImportFromFile(const char * path);

private:
	void boxBlur(unsigned char** newReadableData, int r);
	void boxBlurH(unsigned char** newReadableData, int r);
	void boxBlurT(unsigned char** newReadableData, int r);
	std::vector<int> boxesForGauss(double sigma, int n);
};

#endif