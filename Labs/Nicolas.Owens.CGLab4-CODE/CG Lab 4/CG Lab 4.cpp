#include "Rasterizer.h"

//Variables
Matrix matrices[2]; //0 = View/ 1 = Perspective  
Vertex GridP1[11]; Vertex GridP2[11]; Vertex GridP3[11]; Vertex GridP4[11]; XTime timer;
Vertex Cube1[4] = { {-0.25f, 0.25f, -0.25f,1}, {0.25f, 0.25f, -0.25f,1}, {-0.25f, -0.25f, -0.25f,1}, {0.25f, -0.25f, -0.25f,1} };
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
		VertexShader = VS_View;
		PixelShader = PS_White;
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


	}
	RS_Shutdown();
}

//Vertex v1 = { 1,2,3,4 };
	//Vertex v2 = { 5,6,7,8 };
	//Vertex v3 = { 9,10,11,12 };
	//Vertex v4 = { 13,14,15,16 };
	//Vertex v5 = { 17,18,19,20 };
	//Vertex v6 = { 21,22,23,24 };
	//Vertex v7 = { 25,26,27,28 };
	//Vertex v8 = { 29,30,31,32 };

	//Matrix temp = { v1, v2, v3, v4 };
	//Matrix temo = { v5, v6, v7, v8 };

	//Matrix multi = MatrixTranspose(temp);
	//
	////cout << multi;
	//PrintMatrix4(multi);