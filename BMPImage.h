#pragma once
#include "Color.h"
#include <vector>

class BMPImage
{
public:
	BMPImage(int width, int hight);
	~BMPImage();

	Color GetPixel(int row, int col) const;
	void setPixel(const Color& color, int row, int col);

private:
	int mWidth;
	int mHeight;
	std::vector<Color> mPixels;
};