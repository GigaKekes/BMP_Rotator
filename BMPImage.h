#ifndef BMP_IMAGE_H
#define BMP_IMAGE_H

#define CLOCKWISE_ROTATION 0
#define CONTER_CLOCKWISE_ROTATION 1

#include <vector>
#include "BMPHeader.h"

class BMPImage
{
public:
	BMPHeader bmpHeader;
	unsigned char* garbage;

	unsigned char** readableData;
	BMPImage(const char* path);
	~BMPImage();

	void RotateImage(int direction);
	void ApplyGaussianBluring(int radius);

	void ExportToFile(const char * path);
	void ImportFromFile(const char * path);

private:
	void boxBlur(unsigned char** newReadableData, int radius);
	void boxBlurH(unsigned char** newReadableData, int radius);
	void boxBlurT(unsigned char** newReadableData, int radius);
	std::vector<int> boxesForGauss(double sigma, int n);
};
 
#endif