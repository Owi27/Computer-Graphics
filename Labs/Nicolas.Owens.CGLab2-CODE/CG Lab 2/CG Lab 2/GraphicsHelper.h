#pragma once
#include <iostream>
#include <cmath>
using namespace std;

class GraphicsHelper
{
public:
	int PixelLocation(int _x, int _y, int width);

	void ClearBuffer(unsigned int* _sourceArr, int _width, int height, unsigned int _colorCode);

	void FillPixel(unsigned int* _rasterArr, int _pixelLocation, unsigned int _colorCode);

	unsigned int Interpolate(unsigned int _colorCode1, unsigned int _colorCode2);
	
	unsigned int Interpolate(unsigned int _colorCode1, unsigned int _colorCode2, float _ratio);

	void Bresenham(unsigned int* _sourceArr, int _sourceArrWidth, float _startX, float _startY, float _endX, float _endY, unsigned int _colorCode);

	void Parametric(unsigned int* _sourceArr, int _sourceArrWidth, float _startX, float _startY, float _endX, float _endY, unsigned int _colorCode, unsigned int _colorCode2);
	
	void Parametric(unsigned int* _sourceArr, int _sourceArrWidth, float _startX, float _startY, float _endX, float _endY, unsigned int _colorCode);
	
	void Midpoint(unsigned int* _sourceArr, int _sourceArrWidth, float _startX, float _startY, float _endX, float _endY, unsigned int _colorCode);

	float Lerp(float _num1, float _num2, float _t);

	float ImplicitLineEquation(float _X, float _Y, float _x1, float _y1, float _x2, float _y2);
};

