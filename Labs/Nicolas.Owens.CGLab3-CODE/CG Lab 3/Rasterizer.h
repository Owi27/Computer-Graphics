#include "Shaders.h"

void ClearBuffer(unsigned int _colorCode)
{
	for (size_t i = 0; i < (RasterWidth * RasterHeight); i++)
	{
		Raster[i] = _colorCode;
	}
}

void FillPixel(unsigned int _pixelLocation, unsigned int _colorCode)
{
	Raster[_pixelLocation] = _colorCode;
}

void Bresenham(float _startX, float _startY, float _endX, float _endY, unsigned int _colorCode)
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
				FillPixel(PixelLocation(currX, i), _colorCode);
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
				FillPixel(PixelLocation(currX, i), _colorCode);
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
				FillPixel(PixelLocation(i, currY), _colorCode);
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
				FillPixel(PixelLocation(i, currY), _colorCode);
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

void Bresenham(const Vertex& _vertex1, const Vertex& _vertex2, unsigned int _colorCode)
{
	Vertex copyV1 = _vertex1;
	Vertex copyV2 = _vertex2;

	if (VertexShader != nullptr)
	{
		VertexShader(copyV1);
		VertexShader(copyV2);
	}

	Vertex screenP1 = NdcToScreen(copyV1);
	Vertex screenP2 = NdcToScreen(copyV2);

	float xDelta = (screenP2.X - screenP1.X);
	float yDelta = (screenP2.Y - screenP1.Y);

	float absX = abs(xDelta);
	float absY = abs(yDelta);

	float currY = screenP1.Y;
	float currX = screenP1.X;
	float error = 0.0f;

	//If for different scenario.. If Y base, If X base
	if (absY > absX)
	{
		//Loop Y
		float slope = xDelta / yDelta;

		if (yDelta < 0)
		{
			for (size_t i = screenP1.Y; i > screenP2.Y; i--)
			{
				FillPixel(PixelLocation(currX, i), _colorCode);
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
			for (size_t i = screenP1.Y; i < screenP2.Y; i++)
			{
				FillPixel(PixelLocation(currX, i), _colorCode);
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
			for (size_t i = screenP1.X; i > screenP2.X; i--)
			{
				FillPixel(PixelLocation(i, currY), _colorCode);
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
			for (size_t i = screenP1.X; i < screenP2.X; i++)
			{
				FillPixel(PixelLocation(i, currY), _colorCode);
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

void Parametric(float _startX, float _startY, float _endX, float _endY, unsigned int _colorCode)
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
				FillPixel(PixelLocation(i, floor(CurrY + 0.5)), _colorCode);
			}
		}
		else
		{
			for (size_t i = _startX; i < _endX; i++)
			{
				float Ratio = (i - _startX) / xDelta;
				float CurrY = Lerp(_startY, _endY, Ratio);
				FillPixel(PixelLocation(i, floor(CurrY + 0.5)), _colorCode);
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
				FillPixel(PixelLocation(floor(CurrX + 0.5f), i), _colorCode);
			}
		}
		else
		{
			for (size_t i = _startY; i < _endY; i++)
			{
				float Ratio = (i - _startY) / yDelta;
				float CurrX = Lerp(_startX, _endX, Ratio);
				FillPixel(PixelLocation(floor(CurrX + 0.5), i), _colorCode);
			}
		}
	}


}

void Parametric(const Vertex& _vertex1, const Vertex& _vertex2, unsigned int _colorCode)
{
	Vertex copyV1 = _vertex1;
	Vertex copyV2 = _vertex2;

	if (VertexShader != nullptr)
	{
		VertexShader(copyV1);
		VertexShader(copyV2);
	}

	Vertex screenP1 = NdcToScreen(copyV1);
	Vertex screenP2 = NdcToScreen(copyV2);

	float xDelta = screenP2.X - screenP1.X;
	float yDelta = screenP2.Y - screenP1.Y;

	float absX = abs(xDelta);
	float absY = abs(yDelta);

	if (absX > absY)
	{
		//Loop X
		if (xDelta < 0)
		{
			for (size_t i = screenP1.X; i > screenP2.X; i--)
			{
				float Ratio = (i - screenP1.X) / xDelta;
				float CurrY = Lerp(screenP1.Y, screenP2.Y, Ratio);
				FillPixel(PixelLocation(i, floor(CurrY + 0.5)), _colorCode);
			}
		}
		else
		{
			for (size_t i = screenP1.X; i < screenP2.X; i++)
			{
				float Ratio = (i - screenP1.X) / xDelta;
				float CurrY = Lerp(screenP1.Y, screenP2.Y, Ratio);
				FillPixel(PixelLocation(i, floor(CurrY + 0.5)), _colorCode);
			}
		}
	}
	else
	{
		//Loop Y
		if (yDelta < 0)
		{
			for (size_t i = screenP1.Y; i > screenP2.Y; i--)
			{
				float Ratio = (i - screenP1.Y) / yDelta;
				float CurrX = Lerp(screenP1.X, screenP2.X, Ratio);
				FillPixel(PixelLocation(floor(CurrX + 0.5f), i), _colorCode);
			}
		}
		else
		{
			for (size_t i = screenP1.Y; i < screenP2.Y; i++)
			{
				float Ratio = (i - screenP1.Y) / yDelta;
				float CurrX = Lerp(screenP1.X, screenP2.X, Ratio);
				FillPixel(PixelLocation(floor(CurrX + 0.5), i), _colorCode);
			}
		}
	}


}

void Parametric(float _startX, float _startY, float _endX, float _endY, unsigned int _colorCode, unsigned int _colorCode2)
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
				FillPixel(PixelLocation(i, floor(CurrY + 0.5)), Interpolate(_colorCode, _colorCode2, Ratio));
			}
		}
		else
		{
			for (size_t i = _startX; i < _endX; i++)
			{
				float Ratio = (i - _startX) / xDelta;
				float CurrY = Lerp(_startY, _endY, Ratio);
				FillPixel(PixelLocation(i, floor(CurrY + 0.5)), Interpolate(_colorCode, _colorCode2, Ratio));
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
				FillPixel(PixelLocation(floor(CurrX + 0.5f), i), Interpolate(_colorCode, _colorCode2, Ratio));
			}
		}
		else
		{
			for (size_t i = _startY; i < _endY; i++)
			{
				float Ratio = (i - _startY) / yDelta;
				float CurrX = Lerp(_startX, _endX, Ratio);
				FillPixel(PixelLocation(floor(CurrX + 0.5), i), Interpolate(_colorCode, _colorCode2, Ratio));
			}
		}
	}


}

void Midpoint(float _startX, float _startY, float _endX, float _endY, unsigned int _colorCode)
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
				FillPixel(PixelLocation(i, CurrY), _colorCode);
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
				FillPixel(PixelLocation(i, CurrY), _colorCode);
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
				FillPixel(PixelLocation(CurrX, i), _colorCode);
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
				FillPixel(PixelLocation(CurrX, i), _colorCode);
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

unsigned int BlendTriangle(unsigned int _color1, unsigned int _color2, unsigned int _color3, Vertex _vertex)
{
	/*Color 1*/
	unsigned int Col1A = (_color1 & 0xFF000000) >> 24;
	unsigned int Col1R = (_color1 & 0x00FF0000) >> 16;
	unsigned int Col1G = (_color1 & 0x0000FF00) >> 8;
	unsigned int Col1B = (_color1 & 0x000000FF);

	/*Color 2*/
	unsigned int Col2A = (_color2 & 0xFF000000) >> 24;
	unsigned int Col2R = (_color2 & 0x00FF0000) >> 16;
	unsigned int Col2G = (_color2 & 0x0000FF00) >> 8;
	unsigned int Col2B = (_color2 & 0x000000FF);

	/*Color 3*/
	unsigned int Col3A = (_color3 & 0xFF000000) >> 24;
	unsigned int Col3R = (_color3 & 0x00FF0000) >> 16;
	unsigned int Col3G = (_color3 & 0x0000FF00) >> 8;
	unsigned int Col3B = (_color3 & 0x000000FF);

	float verAlpha = _vertex.X;
	float verBeta = _vertex.Y;
	float verGamma = _vertex.Z;

	unsigned int blendedRed = (Col1R * verAlpha) + (Col2R * verBeta) + (Col3R * verGamma);
	unsigned int blendedGreen = (Col1G * verAlpha) + (Col2G * verBeta) + (Col3G * verGamma);
	unsigned int blendedBlue = (Col1B * verAlpha) + (Col2B * verBeta) + (Col3B * verGamma);

	return blendedRed << 16 | blendedGreen << 8 | blendedBlue;
}

void FillTriangle(unsigned int _colorCode, float _p1X, float _p1Y, float _p2X, float _p2Y, float _p3X, float _p3Y)
{
	for (size_t j = 0; j < RasterHeight; j++)
	{
		for (size_t i = 0; i < RasterWidth; i++)
		{
			Vertex bya = BarycentricCoordinates(_p1X, _p1Y, _p2X, _p2Y, _p3X, _p3Y, i, j);
			if (bya.X >= 0 && bya.X <= 1 &&
				bya.Y >= 0 && bya.Y <= 1 &&
				bya.Z >= 0 && bya.Z <= 1)
			{
				FillPixel(PixelLocation(i, j), _colorCode);
			}
		}
	}

}

void FillTriangle(Vertex _ver1, Vertex _ver2, Vertex _ver3)
{
	Vertex copyVer1 = _ver1;
	Vertex copyVer2 = _ver2;
	Vertex copyVer3 = _ver3;

	if (VertexShader != nullptr)
	{
		VertexShader(copyVer1);
		VertexShader(copyVer2);
		VertexShader(copyVer3);
	}

	 Vertex screenVer1 = NdcToScreen(copyVer1);
	 Vertex screenVer2 = NdcToScreen(copyVer2);
	 Vertex screenVer3 = NdcToScreen(copyVer3);

	for (size_t j = 0; j < RasterHeight; j++)
	{
		for (size_t i = 0; i < RasterWidth; i++)
		{
			Vertex bya = BarycentricCoordinates(screenVer1, screenVer2, screenVer3, i, j);
			if (bya.X >= 0 && bya.X <= 1 &&
				bya.Y >= 0 && bya.Y <= 1 &&
				bya.Z >= 0 && bya.Z <= 1)
			{
				FillPixel(PixelLocation(i, j), BlendTriangle(0xFFFF0000, 0xFF00FF00, 0xFF0000FF, bya));
			}
		}
	}
}

void DrawLine(const Vertex& _start, const Vertex& _end)
{
	Vertex copyStart = _start;
	Vertex copyEnd = _end;

	if (VertexShader)
	{
		VertexShader(copyStart);
		VertexShader(copyEnd);
	}

	Vertex screenStartXY = NdcToScreen(copyStart);
	Vertex screenEndXY = NdcToScreen(copyEnd);

	for (size_t j = 0; j < RasterWidth; j++)
	{
		for (size_t i = 0; i < RasterHeight; i++)
		{
			Pixel copyColor = { Interpolate(copyStart.ColorCode, copyEnd.ColorCode) };
			if (PixelShader)
				PixelShader(copyColor);

			FillPixel(PixelLocation(i, j), copyColor.Color);
		}
	}
}