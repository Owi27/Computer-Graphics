#include "Rasterizer.h"

//Variables
Vertex vertices[3];

//Variables
const Vertex temp[3] = { { 0.0f, +0.5f,0.0f,0.0f, 0xFFFF0000 }, { -0.5f, -0.5f, 0.0f,0.0f, 0xFF00FF00 }, { 0.5f, -0.5f, 0.0f,0.0f, 0xFF0000FF} }; XTime timer;


int main()
{
	RS_Initialize(RasterWidth, RasterHeight);

	while (RS_Update(Raster, PixelCount))
	{
		timer.Signal();
		ClearBuffer(0x00000000);

		VertexShader = VS_World;
		PixelShader = PS_White;
		SV_Matrix = MatrixZRotate(timer.TotalTime());

		Parametric(temp[0], temp[1], 0xFFFFFFFF);
		Parametric(temp[1], temp[2], 0xFFFFFFFF);
		Parametric(temp[2], temp[0], 0xFFFFFFFF);

		FillTriangle(temp[0], temp[1], temp[2]);
	}

	RS_Shutdown();

}
