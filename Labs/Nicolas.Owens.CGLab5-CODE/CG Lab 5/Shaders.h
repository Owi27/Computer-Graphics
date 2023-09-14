#include "MyMath.h"

void (*VertexShader) (Vertex&) = 0;

void (*PixelShader) (Pixel&, Vertex&) = 0;



Matrix SV_Matrix;

void VS_World(Vertex& _multiplyMe)
{
	_multiplyMe = MultiplyMatrixVertex(SV_Matrix, _multiplyMe);
}

void VS_View(Vertex& _multiplyMe)
{
	// CA: These matrices can be calculated ONCE outside this shader, instead of for every shader pass (they don't change for each shader pass)
	Matrix view = MatrixInverse(camera);
	Matrix projection = PerspectiveProjection();

	Matrix viewXWorld = MultiplyMatrix(SV_Matrix, view);
	Matrix projected = MultiplyMatrix(viewXWorld, projection);

	_multiplyMe = MultiplyMatrixVertex(projected, _multiplyMe);
	_multiplyMe.X = _multiplyMe.X / _multiplyMe.W;
	_multiplyMe.Y = _multiplyMe.Y / _multiplyMe.W;
	_multiplyMe.Z = _multiplyMe.Z / _multiplyMe.W;
	_multiplyMe.W = 1;
}

void PS_White(Pixel& _makeWhite)
{
	_makeWhite.Color = 0xFFFFFFFF;
}

void PS_UVTex(Pixel& _pixel, Vertex& _vertex)
{
	unsigned int x = static_cast<int>(_vertex.U * TexWidth);
	unsigned int y = static_cast<int>(_vertex.V * TexHeight);

	_pixel.Color = ColorConversion(TexPixels[static_cast<unsigned int>(x + y * TexWidth)]);
}
