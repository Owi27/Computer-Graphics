using namespace std;

//Includes
#include <iostream>
#include <vector>
#include "RasterSurface.h"
#include "XTime.h"
#include "Madara.h"

//Macros
#define RasterWidth 600
#define RasterHeight 500
#define PixelCount (RasterWidth * RasterHeight)
#define NearPlane 0.1
#define FarPlane 10
#define VertFOV 90
#define AspectRatio (static_cast<float>(RasterHeight) / static_cast<float>(RasterWidth))

#define TexWidth Madara_width
#define TexHeight Madara_height

//Structures
struct Vertex
{
	float X;
	float Y;
	float Z;
	float W;

	float U;
	float V;

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
float ZBuffer[PixelCount];
const unsigned int* TexPixels = Madara_pixels;

XTime timer;
Matrix camera;