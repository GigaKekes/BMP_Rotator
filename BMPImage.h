#pragma once
#include "Color.h"
#include <vector>

class BMPImage
{
public:
	BMPImage(int width, int hight);
	~BMPImage();

	Color GetPixel(int row, int col) const;
	void SetPixel(const Color& color, int row, int col);
	
	void RotateIamge();
	
	void ExportToFile(const char * path);
	void ImportFromFile(const char * path);

private:
	int mWidth;
	int mHeight;
	std::vector<Color> mPixels;
};