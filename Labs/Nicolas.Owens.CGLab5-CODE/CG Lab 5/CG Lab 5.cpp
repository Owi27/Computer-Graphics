#include "Rasterizer.h"

//Variables
Vertex GridP1[11]; Vertex GridP2[11]; Vertex GridP3[11]; Vertex GridP4[11];
Vertex Cube1[4] = { {-0.25f, 0.25f, -0.25f, 1, 0, 0}, {0.25f, 0.25f, -0.25f, 1, 1, 0}, {-0.25f, -0.25f, -0.25f, 1, 0, 1}, {0.25f, -0.25f, -0.25f, 1, 1, 1} };
Vertex Cube2[4] = { {-0.25f, 0.25f, 0.25f,1}, {0.25f, 0.25f, 0.25f,1}, {-0.25, -0.25f, 0.25f,1}, {0.25f,-0.25f,0.25f,1} };

int main()
{
	//Grid
	for (size_t i = 0; i < 11; i++)
	{
		Vertex temp1;
		Vertex temp2;
		Vertex temp3;
		Vertex temp4;

		temp1.X = -0.5f + 0.1f * i;
		temp1.Y = 0.0f;
		temp1.Z = 0.5f;
		temp1.W = 1;

		temp2.X = 0.5f;
		temp2.Y = 0.0f;
		temp2.Z = -0.5f + 0.1f * i;
		temp2.W = 1;

		temp3.X = -0.5 + 0.1f * i;
		temp3.Y = 0.0f;
		temp3.Z = -0.5f;
		temp3.W = 1;

		temp4.X = -0.5f;
		temp4.Y = 0.0f;
		temp4.Z = -0.5 + 0.1f * i;
		temp4.W = 1;

		GridP1[i] = temp1;
		GridP2[i] = temp2;
		GridP3[i] = temp3;
		GridP4[i] = temp4;
	}

	Matrix identity =
	{
		{ 1,0,0,0 },
		{ 0,1,0,0 },
		{ 0,0,1,0 },
		{ 0,0,0,1 }
	};

	Matrix CubeTranslate =
	{
		{ 1,0,0,0 },
		{ 0,1,0,0 },
		{ 0,0,1,0 },
		{ 0,0.25f,0,1 }
	};

	Matrix translate2 =
	{
		{1,0,0,0},
		{0,1,0,0},
		{0,0,1,0},
		{0,0,-1,1}
	};

	Matrix view = MatrixXRotate(-0.314);
	camera = MultiplyMatrix(translate2, view);

	RS_Initialize(RasterWidth, RasterHeight);


	while (RS_Update(Raster, PixelCount))
	{
		timer.Signal();

		ClearBuffer(0x00000000);
		ClearZBuffer();

		//Reset Cube Color
		for (size_t i = 0; i < 4; i++)
		{
			//Back Square
			Cube1[i].ColorCode = 0xFF68EA34;
			//Front Square
			Cube2[i].ColorCode = 0xFFA929EE;
		}

		// CA: recalculate matrices here?

		VertexShader = VS_View;
		PixelShader = PS_UVTex;
		SV_Matrix = identity;

		for (size_t i = 0; i < 11; i++)
		{
			Parametric(GridP1[i], GridP3[i], 0xFFFFFFFF);
			Parametric(GridP2[i], GridP4[i], 0xFFFFFFFF);
		}

		SV_Matrix = MatrixYRotate(timer.TotalTime());
		SV_Matrix = MultiplyMatrix(MatrixYRotate(timer.TotalTime()), CubeTranslate);

		/*Draw Cube*/
		Parametric(Cube1[0], Cube1[1], 0xFF00FF00);
		Parametric(Cube1[1], Cube1[3], 0xFF00FF00);
		Parametric(Cube1[3], Cube1[2], 0xFF00FF00);
		Parametric(Cube1[2], Cube1[0], 0xFF00FF00);
		Parametric(Cube2[0], Cube2[1], 0xFF00FF00);
		Parametric(Cube2[1], Cube2[3], 0xFF00FF00);
		Parametric(Cube2[3], Cube2[2], 0xFF00FF00);
		Parametric(Cube2[2], Cube2[0], 0xFF00FF00);
		Parametric(Cube1[0], Cube2[0], 0xFF00FF00);
		Parametric(Cube1[1], Cube2[1], 0xFF00FF00);
		Parametric(Cube1[2], Cube2[2], 0xFF00FF00);
		Parametric(Cube1[3], Cube2[3], 0xFF00FF00);

		/*CUBE COLORING*/
		//Back
		Cube1[0].U = 1;
		Cube1[0].V = 0;
		Cube1[1].U = 0;
		Cube1[1].V = 0;
		Cube1[2].U = 1;
		Cube1[2].V = 1;
		Cube1[3].U = 0;
		Cube1[3].V = 1;
		FillTriangle(Cube1[0], Cube1[1], Cube1[3]);
		FillTriangle(Cube1[0], Cube1[2], Cube1[3]);

		/*Front*/
		Cube2[0].U = 0;
		Cube2[0].V = 0;
		Cube2[1].U = 1;
		Cube2[1].V = 0;
		Cube2[2].U = 0;
		Cube2[2].V = 1;
		Cube2[3].U = 1;
		Cube2[3].V = 1;
		FillTriangle(Cube2[0], Cube2[1], Cube2[3]);
		FillTriangle(Cube2[0], Cube2[2], Cube2[3]);

		/*Top & Bottom*/
		//for (size_t i = 0; i < 4; i++)
		//{
		//	Cube1[i].ColorCode = 0xFFFCC9B9;
		//	Cube2[i].ColorCode = 0xFFFCC9B9;
		//}
		//Top
		Cube1[0].U = 0;
		Cube1[0].V = 0;
		Cube1[1].U = 1;
		Cube1[1].V = 0;
		Cube2[0].U = 0;
		Cube2[0].V = 1;
		Cube2[1].U = 1;
		Cube2[1].V = 1;
		FillTriangle(Cube1[0], Cube2[0], Cube2[1]);
		FillTriangle(Cube1[0], Cube1[1], Cube2[1]);
		//Bottom
		Cube1[2].U = 0;
		Cube1[2].V = 0;
		Cube1[3].U = 1;
		Cube1[3].V = 0;
		Cube2[2].U = 0;
		Cube2[2].V = 1;
		Cube2[3].U = 1;
		Cube2[3].V = 1;
		FillTriangle(Cube1[2], Cube2[2], Cube2[3]);
		FillTriangle(Cube1[2], Cube1[3], Cube2[3]);

		/*Sides*/
		//for (size_t i = 0; i < 4; i++)
		//{
		//	Cube1[i].ColorCode = 0xFF89CFF0;
		//	Cube2[i].ColorCode = 0xFF89CFF0;
		//}
		Cube1[0].U = 0;
		Cube1[0].V = 0;
		Cube1[2].U = 0;
		Cube1[2].V = 1;
		Cube2[0].U = 1;
		Cube2[0].V = 0;
		Cube2[2].U = 1;
		Cube2[2].V = 1;
		FillTriangle(Cube1[0], Cube1[2], Cube2[2]);
		FillTriangle(Cube1[0], Cube2[0], Cube2[2]);
		//for (size_t i = 0; i < 4; i++)
		//{
		//	Cube1[i].ColorCode = 0xFFFF0000;
		//	Cube2[i].ColorCode = 0xFFFF0000;
		//}
		//OtherSide
		Cube1[1].U = 1;
		Cube1[1].V = 0;
		Cube1[3].U = 1;
		Cube1[3].V = 1;
		Cube2[1].U = 0;
		Cube2[1].V = 0;
		Cube2[3].U = 0;
		Cube2[3].V = 1;
		FillTriangle(Cube1[1], Cube1[3], Cube2[3]);
		FillTriangle(Cube1[1], Cube2[1], Cube2[3]);
	}

	RS_Shutdown();
	return 0;
}