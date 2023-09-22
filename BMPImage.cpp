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
	return mPixels[col * mWidth + row];
}

void BMPImage::SetPixel(const Color& color, int row, int col)
{
	mPixels[col * mWidth + row].red = color.red;
	mPixels[col * mWidth + row].green = color.green;
	mPixels[col * mWidth + row].blue = color.blue;
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
