// CG Lab 1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include "RasterSurface.h"
#include "tiles_12.h"
#include "XTime.h"
#include "blood_hit_04.h"
using namespace std;

//Variables
unsigned int Raster[250000]; XTime timer;
vector<RECT> Sprites;

//Functions
int PixelLocation(int _x, int _y, int width); void ClearBuffer(int _width, int height, unsigned int _colorCode);
void FillPixel(unsigned int* _rasterArray, int _pixelLocation, unsigned int _colorCode); unsigned int ColorConversion(unsigned int _colorCode);
void BLIT(const unsigned int* _sourceArr, unsigned int _sourceTexWidth, int _rect1, int _rect2,
	int _rect3, int _rect4, unsigned int _uiRasterX, unsigned int _uiRasterY);
unsigned int Interpolate(unsigned int _colorCode1, unsigned int _colorCode2);

int main()
{
	timer.Restart();

	RS_Initialize(500, 500);

	int pos[20];
	for (size_t i = 0; i < 20; i++)
	{
		pos[i] = (rand() % 501);
	}

	//Rect Arrays Initilize
	for (size_t y = 0; y < (blood_hit_04_width / 128); y++)
	{
		for (size_t x = 0; x < (blood_hit_04_width / 128); x++)
		{
			RECT temp = { (x * 128), (y * 128), (128 + (x * 128)), (128 + (y * 128)) };
			Sprites.push_back(temp);
		}
	}
	
	float elapse = 0.0f;
	int animIdx = 0;
	while (RS_Update(Raster, 250000))
	{
		ClearBuffer(500, 500, 0x000000);
		timer.Signal();
		elapse += timer.Delta();

		/*for (size_t i = 0; i < 250000; i++)
		{
			Raster[i] = Interpolate(0xFFFFFFFF, 0x00000000);
		}*/


		//Background
		for (size_t i = 0; i < 20; i++)
		{
			for (size_t j = 0; j < 20; j++)
			{
				if ((320 - 287) * i <= 500)
				{
					if ((160 - 127) * j <= 500)
					{
						BLIT(tiles_12_pixels, tiles_12_width, 287, 127, 320, 160, (320 - 287) * i, (160 - 127) * j);
					}
				}
			}
		}

		//10 Random Objects
		for (size_t i = 0; i < 10; i++)
		{
			BLIT(tiles_12_pixels, tiles_12_width, 128, 32, 191, 95, pos[i], pos[i + 10]);
		}

		//Animation
		/*Size of 128, loop through image spot to change anim to next frame, figure out xtime for delays*/
		if (elapse >= (1.0f / 30.0f))
		{
			animIdx++;
			elapse = 0.0f;
			if (animIdx >= 16)
			{
				animIdx = 0;
			}

		}
		BLIT(blood_hit_04_pixels, blood_hit_04_width, Sprites[animIdx].top, Sprites[animIdx].left,
			Sprites[animIdx].bottom, Sprites[animIdx].right, 200, 200);

	}

	RS_Shutdown();
}

int PixelLocation(int _x, int _y, int width)
{
	int pixel = (_y * width) + _x;

	return pixel;
}

void ClearBuffer(int _width, int height, unsigned int _colorCode)
{
	for (size_t i = 0; i < (_width * height); i++)
	{
		Raster[i] = _colorCode;
	}
}

void FillPixel(unsigned int* _rasterArr, int _pixelLocation, unsigned int _colorCode)
{
	_rasterArr[_pixelLocation] = _colorCode;
}

void BLIT(const unsigned int* _sourceArr, unsigned int _sourceTexWidth, int _rect1, int _rect2,
	int _rect3, int _rect4, unsigned int _uiRasterX, unsigned int _uiRasterY)
{
	int rectHeight = _rect3 - _rect1;
	int rectWidth = _rect4 - _rect2;

	for (size_t i = 0; i < rectHeight; i++)
	{
		for (size_t j = 0; j < rectWidth; j++)
		{
			if ((_uiRasterX + j) >= 0 && (_uiRasterX + j) < 500 && (_uiRasterY + i) >= 0 && (_uiRasterY + i) < 500)
			{
				//Raster[PixelLocation(_uiRasterX + j, _uiRasterY + i, 500)] = 
				//	ColorConversion(_sourceArr[PixelLocation(_rect1 + j, _rect2 + i, _sourceTexWidth)]);

				unsigned int color_start = Raster[PixelLocation(_uiRasterX + j, _uiRasterY + i, 500)];
				unsigned int color_end = ColorConversion(_sourceArr[PixelLocation(_rect1 + j, _rect2 + i, _sourceTexWidth)]);
				Raster[PixelLocation(_uiRasterX + j, _uiRasterY + i, 500)] = Interpolate(color_start, color_end);
			}
		}
	}
}

unsigned int ColorConversion(unsigned int _colorCode)
{
	unsigned int a = (0x000000FF & _colorCode) << 24;
	unsigned int r = (0x0000FF00 & _colorCode) << 8;
	unsigned int g = (0x00FF0000 & _colorCode) >> 8;
	unsigned int b = (0xFF000000 & _colorCode) >> 24;

	unsigned int temp = a | r | g | b;
	return temp;
}

unsigned int Interpolate(unsigned int _colorCode1, unsigned int _colorCode2)
{
	//XRGB
	unsigned int cc1R = (_colorCode1 & 0x00FF0000) >> 16;
	unsigned int cc1G = (_colorCode1 & 0x0000FF00) >> 8;
	unsigned int cc1B = (_colorCode1 & 0x000000FF);
	unsigned int cc1A = (_colorCode1 & 0xFF000000) >> 24;

	unsigned int cc2R = (_colorCode2 & 0x00FF0000) >> 16;
	unsigned int cc2G = (_colorCode2 & 0x0000FF00) >> 8;
	unsigned int cc2B = (_colorCode2 & 0x000000FF);
	unsigned int cc2A = (_colorCode2 & 0xFF000000) >> 24;

	float R = cc2A / 255.0f;

	//Split color and cast
	unsigned int finR = ((static_cast<int>(cc2R)) - (static_cast<int>(cc1R))) * R + cc1R;
	unsigned int finG = ((static_cast<int>(cc2G)) - (static_cast<int>(cc1G))) * R + cc1G;
	unsigned int finB = ((static_cast<int>(cc2B)) - (static_cast<int>(cc1B))) * R + cc1B;
	unsigned int finA = ((static_cast<int>(cc2A)) - (static_cast<int>(cc1A))) * R + cc1A;

	unsigned int temp = finA << 24 | finR << 16 | finG << 8 | finB;
	return temp;
}

