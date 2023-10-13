#ifndef BMP_IMAGE_H
#define BMP_IMAGE_H

#define CLOCKWISE_ROTATION true
#define CONTER_CLOCKWISE_ROTATION false

#include <vector>
#include "BMPHeader.h"

class BMPImage
{
public:
	BMPHeader bmpHeader; // Header
	unsigned char* garbage; // Bytes between header and pixells
	unsigned char** readableData; // Array of pixels and their rgb components [height * width][3]
	BMPImage(const char* path);
	~BMPImage();

	void RotateImage(bool isColockwise); // Rotation method
	void ApplyGaussianBluring(int radius); // Gaussian bluring applying method

	void ExportToFile(const char* path); 
	void ImportFromFile(const char* path);

private:
	BMPImage& operator=(const BMPImage& other);  // Assignment operator
	BMPImage(const BMPImage& other); //Copy constructor

	void boxBlur(unsigned char** newReadableData, int radius);	// Gaussian bluring helping functiuon
	void boxBlurH(unsigned char** newReadableData, int radius);	// Gaussian bluring helping functiuon
	void boxBlurT(unsigned char** newReadableData, int radius);	// Gaussian bluring helping functiuon
	std::vector<int> boxesForGauss(double sigma, int n);		// Gaussian bluring helping functiuon
};
 
#endif