using namespace std;

//Includes
#include <iostream>
#include <vector>
#include "RasterSurface.h"
#include "XTime.h"

//Macros
#define RasterWidth 500
#define RasterHeight 500
#define PixelCount (RasterWidth * RasterHeight)

//Structures
struct Vertex
{
	float X;
	float Y;
	float Z;
	float W;

	unsigned int ColorCode;
};

struct Matrix
{
	Vertex _1;
	Vertex _2;
	Vertex _3;
	Vertex _4;
};

struct Pixel
{
	unsigned int Color;
};

//Globals
unsigned int Raster[PixelCount];