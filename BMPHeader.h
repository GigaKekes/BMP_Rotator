#ifndef BMP_IMAGE_HEADER_H
#define BMP_IMAGE_HEADER_H

#include <stdint.h>

#pragma pack(1)
typedef struct BMPHeader
{
	uint16_t type;          // Magic identifier "BM" (0x424D)
	uint32_t file_size;     // File size in bytes
	uint16_t reserved1;		// Unused
	uint16_t reserved2;		// Unused
	uint32_t pixelOffset;	// Offset to the start of pixel data
	uint32_t header_size;   // Size of the DIB header (40 bytes)
	int32_t width;          // Image width in pixels
	int32_t height;         // Image height in pixels
	uint16_t planes;        // Number of color planes (1)
	uint16_t bitsPerPixel;	// Bits per pixel (e.g., 24 for RGB and 32 for ARGB)
	uint32_t compression;   // Compression method (0 for no compression)
	uint32_t dataSize;      // Image size in bytes 
	int32_t pWidth;			// Pixels per meter in X direction
	int32_t pHeight;		// Pixels per meter in Y direction
	uint32_t colorsUsed;	// Number of colors used
	uint32_t importantColors; // Number of important colors used
} BMPHeader;
#pragma pop


#endif
