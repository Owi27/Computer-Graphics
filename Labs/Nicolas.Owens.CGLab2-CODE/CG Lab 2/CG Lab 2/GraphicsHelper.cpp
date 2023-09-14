#include "GraphicsHelper.h"

int GraphicsHelper::PixelLocation(int _x, int _y, int width)
{
	int pixel = (_y * width) + _x;

	return pixel;
}

void GraphicsHelper::ClearBuffer(unsigned int* _sourceArr, int _width, int height, unsigned int _colorCode)
{
	for (size_t i = 0; i < (_width * height); i++)
	{
		_sourceArr[i] = _colorCode;
	}
}

void GraphicsHelper::FillPixel(unsigned int* _rasterArr, int _pixelLocation, unsigned int _colorCode)
{
	if (_pixelLocation < 250000)
		_rasterArr[_pixelLocation] = _colorCode;
}

unsigned int GraphicsHelper::Interpolate(unsigned int _colorCode1, unsigned int _colorCode2)
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

unsigned int GraphicsHelper::Interpolate(unsigned int _colorCode1, unsigned int _colorCode2, float _ratio)
{
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

void GraphicsHelper::Bresenham(unsigned int* _sourceArr, int _sourceArrWidth, float _startX, float _startY, float _endX, float _endY, unsigned int _colorCode)
{
	float xDelta = (_endX - _startX);
	float yDelta = (_endY - _startY);

	float absX = abs(xDelta);
	float absY = abs(yDelta);

	float currY = _startY;
	float currX = _startX;
	float error = 0.0f;

	//If for different scenario.. If Y base, If X base
	if (absY > absX)
	{
		//Loop Y
		float slope = xDelta / yDelta;

		if (yDelta < 0)
		{
			for (size_t i = _startY; i > _endY; i--)
			{
				FillPixel(_sourceArr, PixelLocation(currX, i, _sourceArrWidth), _colorCode);
				error += slope;
				if (slope < 0)
				{
					if (error < -0.5)
					{
						// If Negative
						if (yDelta < 0)
						{
							currX += 1;
						}
						else
							currX -= 1;
						error += 1;
					}
				}
				else
				{
					if (error > 0.5)
					{
						// If Negative
						if (yDelta < 0)
						{
							currX -= 1;
						}
						else
							currX += 1;
						error -= 1;
					}
				}
			}

		}
		else if (yDelta > 0)
		{
			for (size_t i = _startY; i < _endY; i++)
			{
				FillPixel(_sourceArr, PixelLocation(currX, i, _sourceArrWidth), _colorCode);
				error += slope;
				if (error < -0.5)
				{
					if (xDelta < 0)
					{
						currX -= 1;
					}
					else
						currX += 1;
					error += 1;
				}
			}
		}
	}
	else
	{
		//Loop X
		float slope = yDelta / xDelta;

		if (xDelta < 0)
		{
			for (size_t i = _startX; i > _endX; i--)
			{
				FillPixel(_sourceArr, PixelLocation(i, currY, _sourceArrWidth), _colorCode);
				error += slope;
				if (slope < 0)
				{
					if (error < -0.5)
					{
						// If Negative
						if (yDelta < 0)
						{
							currY -= 1;
						}
						else
							currY += 1;
						error += 1;
					}
				}
				else
				{
					if (error > 0.5)
					{
						// If Negative
						if (yDelta < 0)
						{
							currY -= 1;
						}
						else
							currY += 1;
						error -= 1;
					}
				}
			}
		}
		else if (xDelta > 0)
		{
			for (size_t i = _startX; i < _endX; i++)
			{
				FillPixel(_sourceArr, PixelLocation(i, currY, _sourceArrWidth), _colorCode);
				error += slope;
				if (error > 0.5)
				{
					if (yDelta < 0)
					{
						currY -= 1;
					}
					else
						currY += 1;
					error -= 1;
				}
			}
		}
	}
}

void GraphicsHelper::Parametric(unsigned int* _sourceArr, int _sourceArrWidth, float _startX, float _startY, float _endX, float _endY, unsigned int _colorCode, unsigned int _colorCode2)
{
	/*
		for(StartX to EndX)
		{
			Ratio = (CurrX – StartX) / ΔX
			CurrY = Lerp(StartY, EndY, Ratio)
			PlotPixel(CurrX, Floor(CurrY + 0.5))
		}
	*/
	float xDelta = _endX - _startX;
	float yDelta = _endY - _startY;

	float absX = abs(xDelta);
	float absY = abs(yDelta);

	if (absX > absY)
	{
		//Loop X
		if (xDelta < 0)
		{
			for (size_t i = _startX; i > _endX; i--)
			{
				float Ratio = (i - _startX) / xDelta;
				float CurrY = Lerp(_startY, _endY, Ratio);
				FillPixel(_sourceArr, PixelLocation(i, floor(CurrY + 0.5), _sourceArrWidth), Interpolate(_colorCode, _colorCode2, Ratio));
			}
		}
		else
		{
			for (size_t i = _startX; i < _endX; i++)
			{
				float Ratio = (i - _startX) / xDelta;
				float CurrY = Lerp(_startY, _endY, Ratio);
				FillPixel(_sourceArr, PixelLocation(i, floor(CurrY + 0.5), _sourceArrWidth), Interpolate(_colorCode, _colorCode2, Ratio));
			}
		}
	}
	else
	{
		//Loop Y
		if (yDelta < 0)
		{
			for (size_t i = _startY; i > _endY; i--)
			{
				float Ratio = (i - _startY) / yDelta;
				float CurrX = Lerp(_startX, _endX, Ratio);
				FillPixel(_sourceArr, PixelLocation(floor(CurrX + 0.5f), i, _sourceArrWidth), Interpolate(_colorCode, _colorCode2, Ratio));
			}
		}
		else
		{
			for (size_t i = _startY; i < _endY; i++)
			{
				float Ratio = (i - _startY) / yDelta;
				float CurrX = Lerp(_startX, _endX, Ratio);
				FillPixel(_sourceArr, PixelLocation(floor(CurrX + 0.5), i, _sourceArrWidth), Interpolate(_colorCode, _colorCode2, Ratio));
			}
		}
	}
}

void GraphicsHelper::Parametric(unsigned int* _sourceArr, int _sourceArrWidth, float _startX, float _startY, float _endX, float _endY, unsigned int _colorCode)
{
	float xDelta = _endX - _startX;
	float yDelta = _endY - _startY;

	float absX = abs(xDelta);
	float absY = abs(yDelta);

	if (absX > absY)
	{
		//Loop X
		if (xDelta < 0)
		{
			for (size_t i = _startX; i > _endX; i--)
			{
				float Ratio = (i - _startX) / xDelta;
				float CurrY = Lerp(_startY, _endY, Ratio);
				FillPixel(_sourceArr, PixelLocation(i, floor(CurrY + 0.5), _sourceArrWidth), _colorCode);
			}
		}
		else
		{
			for (size_t i = _startX; i < _endX; i++)
			{
				float Ratio = (i - _startX) / xDelta;
				float CurrY = Lerp(_startY, _endY, Ratio);
				FillPixel(_sourceArr, PixelLocation(i, floor(CurrY + 0.5), _sourceArrWidth), _colorCode);
			}
		}
	}
	else
	{
		//Loop Y
		if (yDelta < 0)
		{
			for (size_t i = _startY; i > _endY; i--)
			{
				float Ratio = (i - _startY) / yDelta;
				float CurrX = Lerp(_startX, _endX, Ratio);
				FillPixel(_sourceArr, PixelLocation(floor(CurrX + 0.5f), i, _sourceArrWidth), _colorCode);
			}
		}
		else
		{
			for (size_t i = _startY; i < _endY; i++)
			{
				float Ratio = (i - _startY) / yDelta;
				float CurrX = Lerp(_startX, _endX, Ratio);
				FillPixel(_sourceArr, PixelLocation(floor(CurrX + 0.5), i, _sourceArrWidth), _colorCode);
			}
		}
	}
}

void GraphicsHelper::Midpoint(unsigned int* _sourceArr, int _sourceArrWidth, float _startX, float _startY, float _endX, float _endY, unsigned int _colorCode)
{
	/*
		CurrY = StartY;
		for(StartX to EndX)
		{
			PloatPixel(CurrX, CurrY);
			float MidPoint = CurrX + 1, CurrY + 0.5f;
			if(ImplcitLineEquation(MidPoint) < 0)
			{
				CurrY += 1;
			}
		}
	*/
	float xDelta = _endX - _startX;
	float yDelta = _endY - _startY;

	float absX = abs(xDelta);
	float absY = abs(yDelta);

	float CurrX = _startX;
	float CurrY = _startY;
	if (absX > absY)
	{
		//Loop X
		if (xDelta < 0)
		{
			for (size_t i = _startX; i > _endX; i--)
			{
				FillPixel(_sourceArr, PixelLocation(i, CurrY, _sourceArrWidth), _colorCode);
				float midpointX = i + 1;
				float midpointY = CurrY + 0.5;
				if (ImplicitLineEquation(midpointX, midpointY, _startX, _startY, _endX, _endY) < 0)
				{
					if (yDelta < 0)
					{
						CurrY -= 1;
					}
					else if (yDelta > 0)
					{
						CurrY += 1;
					}
					else
						CurrY = CurrY;
				}
			}
		}
		else {
			for (size_t i = _startX; i < _endX; i++)
			{
				FillPixel(_sourceArr, PixelLocation(i, CurrY, _sourceArrWidth), _colorCode);
				float midpointX = i - 1;
				float midpointY = CurrY + 0.5;
				if (ImplicitLineEquation(midpointX, midpointY, _startX, _startY, _endX, _endY) < 0)
				{
					if (yDelta < 0)
					{
						CurrY -= 1;
					}
					else if (yDelta > 0)
					{
						CurrY += 1;
					}
					else
						CurrY = CurrY;
				}
			}
		}
	}
	else
	{
		//Loop Y
		if (yDelta < 0)
		{
			for (size_t i = _startY; i > _endY; i--)
			{
				FillPixel(_sourceArr, PixelLocation(CurrX, i, _sourceArrWidth), _colorCode);
				float midpointX = CurrX + 0.5;
				float midpointY = i + 1;
				if (ImplicitLineEquation(midpointX, midpointY, _startX, _startY, _endX, _endY) < 0)
				{
					if (xDelta < 0)
					{
						CurrX -= 1;
					}
					else if (xDelta > 0)
					{
						CurrX += 1;
					}
					else
						CurrX = CurrX;
				}
			}
		}
		else
		{
			for (size_t i = _startY; i < _endY; i++)
			{
				FillPixel(_sourceArr, PixelLocation(CurrX, i, _sourceArrWidth), _colorCode);
				float midpointX = CurrX + 0.5;
				float midpointY = i - 1;
				if (ImplicitLineEquation(midpointX, midpointY, _startX, _startY, _endX, _endY) < 0)
				{
					if (xDelta < 0)
					{
						CurrX -= 1;
					}
					else if (xDelta > 0)
					{
						CurrX += 1;
					}
					else
						CurrX = CurrX;
				}
			}
		}
	}
}

float GraphicsHelper::Lerp(float _num1, float _num2, float _t)
{
	return _num1 + _t * (_num2 - _num1);
}

float GraphicsHelper::ImplicitLineEquation(float _X, float _Y, float _x1, float _y1, float _x2, float _y2)
{
	return (_y1 - _y2) * _X + (_x2 - _x1) * _Y + (_x1 * _y2) - (_y1 * _x2);
}
