#include "BMPImage.h"

BMPImage::BMPImage(int width, int height):
	mWidth(width), mHeight(height), mPixels(std::vector<Color>(width*height))
{
}

BMPImage::~BMPImage()
{
}

Color BMPImage::GetPixel(int row, int col) const
{
	return mPixels[row * mWidth + col];
}

void BMPImage::SetPixel(const Color& color, int row, int col)
{
	mPixels[row * mWidth + col].red = color.red;
	mPixels[row * mWidth + col].green = color.green;
	mPixels[row * mWidth + col].blue = color.blue;
}

void BMPImage::RotateIamge()
{
}

void BMPImage::ApplyGaussianBluring()
{
}

void BMPImage::ExportToFile(const char* path)
{
}

void BMPImage::ImportFromFile(const char* path)
{
}
