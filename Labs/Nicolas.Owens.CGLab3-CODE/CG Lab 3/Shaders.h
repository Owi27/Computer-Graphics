#include "MyMath.h"

void (*VertexShader) (Vertex&) = 0;

void (*PixelShader) (Pixel&) = 0;

Matrix SV_Matrix;

void VS_World(Vertex& _multiplyMe)
{
	_multiplyMe = MultiplyMatrixVertex(SV_Matrix, _multiplyMe);
}

void PS_White(Pixel& _makeWhite)
{
	_makeWhite.Color = 0xFFFFFFFF;
}
