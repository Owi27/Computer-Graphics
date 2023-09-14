#include <iostream>
#include <time.h>
#include <vector>
#include <windows.h> 
#include <WinUser.h>
#include "GraphicsHelper.h"
#include "RasterSurface.h"
using namespace std;

//Variables
unsigned int Raster[250000]; GraphicsHelper gHelper;

int main()
{
	srand(time(0));
	RS_Initialize(500, 500);
	gHelper.ClearBuffer(Raster, 500, 500, 0x00000000);

	//Stars
	for (size_t i = 0; i < 2500; i++)
	{
		gHelper.FillPixel(Raster, gHelper.PixelLocation(rand() % 500, rand() % 500, 500), 0xFFFFFFFF);
	}

	while (RS_Update(Raster, 250000))
	{
		gHelper.Bresenham(Raster, 500, 0, 100, 499, 400, 0xFF0000);

		gHelper.Midpoint(Raster, 500, 0, 110, 499, 410, 0x00FF00);

		gHelper.Parametric(Raster, 500, 0, 120, 499, 420, gHelper.Interpolate(0xFF00FF, 0x00FFFF));

		//Random Bresenham Line
		if (GetAsyncKeyState(0x48) & 0x1)
		{
			vector<int> randArr;
			for (size_t i = 0; i < 4; i++)
			{
				randArr.push_back(rand() % 500);
			}
			gHelper.Bresenham(Raster, 500, randArr[0], randArr[1], randArr[2], randArr[3], 0xFF0000);
			gHelper.FillPixel(Raster, gHelper.PixelLocation(randArr[0], randArr[1], 500), 0xFFFF00);
			gHelper.FillPixel(Raster, gHelper.PixelLocation(randArr[2], randArr[3], 500), 0xFFFF00);
		}

		//Random Midpoint Line
		if (GetAsyncKeyState(0x4A) & 0x1)
		{
			vector<int> randArr;
			for (size_t i = 0; i < 4; i++)
			{
				randArr.push_back(rand() % 500);
			}
			gHelper.Midpoint(Raster, 500, randArr[0], randArr[1], randArr[2], randArr[3], 0x00FF00);
			gHelper.FillPixel(Raster, gHelper.PixelLocation(randArr[0], randArr[1], 500), 0xFFFF00);
			gHelper.FillPixel(Raster, gHelper.PixelLocation(randArr[2], randArr[3], 500), 0xFFFF00);
		}

		//Random Parametric Line
		if (GetAsyncKeyState(0x4B) & 0x1)
		{
			vector<int> randArr;
			for (size_t i = 0; i < 4; i++)
			{
				randArr.push_back(rand() % 500);
			}
			gHelper.Parametric(Raster, 500, randArr[0], randArr[1], randArr[2], randArr[3], gHelper.Interpolate(0xFF00FF, 0x00FFFF));
			gHelper.FillPixel(Raster, gHelper.PixelLocation(randArr[0], randArr[1], 500), 0xFFFF00);
			gHelper.FillPixel(Raster, gHelper.PixelLocation(randArr[2], randArr[3], 500), 0xFFFF00);
		}

		////Test Cases - All 3 Succeeded
		// //X
		 /*gHelper.Parametric(Raster, 500, 250, 250, 0, 0, 0xFFFFFF);
		 gHelper.Parametric(Raster, 500, 250, 250, 499, 0, 0xFFFFFF);
		 gHelper.Parametric(Raster, 500, 250, 250, 0, 499, 0xFFFFFF);
		 gHelper.Parametric(Raster, 500, 250, 250, 499, 499, 0xFFFFFF);*/
		 // //+    
		 // gHelper.Midpoint(Raster, 500, 250, 250, 250, 0, 0xFFFFFF);
		 // gHelper.Midpoint(Raster, 500, 250, 250, 250, 499, 0xFFFFFF);
		 // gHelper.Midpoint(Raster, 500, 250, 250, 0, 250, 0xFFFFFF);
		 // gHelper.Midpoint(Raster, 500, 250, 250, 499, 250, 0xFFFFFF);

	}

	RS_Shutdown();
	return 0;
}
