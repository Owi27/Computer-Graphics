#include "Defines.h"

unsigned int PixelLocation(int _x, int _y)
{
	int pixel = (_y * RasterWidth) + _x;

	return pixel;
}

unsigned int Interpolate(unsigned int _colorCode1, unsigned int _colorCode2)
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

unsigned int Interpolate(unsigned int _colorCode1, unsigned int _colorCode2, float _ratio)
{
	unsigned int cc1R = (_colorCode1 & 0x00FF0000) >> 16;
	unsigned int cc1G = (_colorCode1 & 0x0000FF00) >> 8;
	unsigned int cc1B = (_colorCode1 & 0x000000FF);
	unsigned int cc1A = (_colorCode1 & 0xFF000000) >> 24;

	unsigned int cc2R = (_colorCode2 & 0x00FF0000) >> 16;
	unsigned int cc2G = (_colorCode2 & 0x0000FF00) >> 8;
	unsigned int cc2B = (_colorCode2 & 0x000000FF);
	unsigned int cc2A = (_colorCode2 & 0xFF000000) >> 24;

	float R = _ratio;

	//Split color and cast
	unsigned int finR = ((static_cast<int>(cc2R)) - (static_cast<int>(cc1R))) * R + cc1R;
	unsigned int finG = ((static_cast<int>(cc2G)) - (static_cast<int>(cc1G))) * R + cc1G;
	unsigned int finB = ((static_cast<int>(cc2B)) - (static_cast<int>(cc1B))) * R + cc1B;
	unsigned int finA = ((static_cast<int>(cc2A)) - (static_cast<int>(cc1A))) * R + cc1A;

	unsigned int temp = finA << 24 | finR << 16 | finG << 8 | finB;
	return temp;
}

float Lerp(float _num1, float _num2, float _t)
{
	return _num1 + _t * (_num2 - _num1);
}

float ImplicitLineEquation(float _X, float _Y, float _x1, float _y1, float _x2, float _y2)
{
	return (_y1 - _y2) * _X + (_x2 - _x1) * _Y + (_x1 * _y2) - (_y1 * _x2);
}

Vertex BarycentricCoordinates(float _p1X, float _p1Y, float _p2X, float _p2Y, float _p3X, float _p3Y,
	float _X, float _Y)
{
	Vertex temp;

	float Beta = ImplicitLineEquation(_p2X, _p2Y, _p1X, _p1Y, _p3X, _p3Y);
	float Gamma = ImplicitLineEquation(_p3X, _p3Y, _p2X, _p2Y, _p1X, _p1Y);
	float Alpha = ImplicitLineEquation(_p1X, _p1Y, _p3X, _p3Y, _p2X, _p2Y);
	float b = ImplicitLineEquation(_X, _Y, _p1X, _p1Y, _p3X, _p3Y);
	float y = ImplicitLineEquation(_X, _Y, _p2X, _p2Y, _p1X, _p1Y);
	float a = ImplicitLineEquation(_X, _Y, _p3X, _p3Y, _p2X, _p2Y);

	temp.X = a / Alpha;
	temp.Y = b / Beta;
	temp.Z = y / Gamma;

	return temp;
}

Vertex BarycentricCoordinates(Vertex _ver1, Vertex _ver2, Vertex _ver3, float _X, float _Y)
{
	Vertex temp;

	float Beta = ImplicitLineEquation(_ver2.X, _ver2.Y, _ver1.X, _ver1.Y, _ver3.X, _ver3.Y);
	float Gamma = ImplicitLineEquation(_ver3.X, _ver3.Y, _ver2.X, _ver2.Y, _ver1.X, _ver1.Y);
	float Alpha = ImplicitLineEquation(_ver1.X, _ver1.Y, _ver3.X, _ver3.Y, _ver2.X, _ver2.Y);
	float b = ImplicitLineEquation(_X, _Y, _ver1.X, _ver1.Y, _ver3.X, _ver3.Y);
	float y = ImplicitLineEquation(_X, _Y, _ver2.X, _ver2.Y, _ver1.X, _ver1.Y);
	float a = ImplicitLineEquation(_X, _Y, _ver3.X, _ver3.Y, _ver2.X, _ver2.Y);

	temp.X = a / Alpha;
	temp.Y = b / Beta;
	temp.Z = y / Gamma;

	return temp;
}

void PrintMatrix3(Matrix _matrix)
{
	cout << _matrix._1.X << " " << _matrix._1.Y << " " << _matrix._1.Z << endl;
	cout << _matrix._2.X << " " << _matrix._2.Y << " " << _matrix._2.Z << endl;
	cout << _matrix._3.X << " " << _matrix._3.Y << " " << _matrix._3.Z << endl;
}

void PrintMatrix4(Matrix _matrix)
{
	cout << _matrix._1.X << " " << _matrix._1.Y << " " << _matrix._1.Z << endl;
	cout << _matrix._2.X << " " << _matrix._2.Y << " " << _matrix._2.Z << endl;
	cout << _matrix._3.X << " " << _matrix._3.Y << " " << _matrix._3.Z << endl;
	cout << _matrix._4.X << " " << _matrix._4.Y << " " << _matrix._4.Z << endl;
}

Matrix MultiplyMatrix3x3(Matrix _matrix1, Matrix _matrix2)
{
	Matrix temp;
	Vertex Row1;
	Vertex Row2;
	Vertex Row3;

	/*Multiplication Logic*/
	//Row 1
	Row1.X = (_matrix1._1.X * _matrix2._1.X) + (_matrix1._1.Y * _matrix2._2.X) + (_matrix1._1.Z * _matrix2._3.X);
	Row1.Y = (_matrix1._1.X * _matrix2._1.Y) + (_matrix1._1.Y * _matrix2._2.Y) + (_matrix1._1.Z * _matrix2._3.Y);
	Row1.Z = (_matrix1._1.X * _matrix2._1.Z) + (_matrix1._1.Y * _matrix2._2.Z) + (_matrix1._1.Z * _matrix2._3.Z);

	//Row 2
	Row2.X = (_matrix1._2.X * _matrix2._1.X) + (_matrix1._2.Y * _matrix2._2.X) + (_matrix1._2.Z * _matrix2._3.X);
	Row2.Y = (_matrix1._2.X * _matrix2._1.Y) + (_matrix1._2.Y * _matrix2._2.Y) + (_matrix1._2.Z * _matrix2._3.Y);
	Row2.Z = (_matrix1._2.X * _matrix2._1.Z) + (_matrix1._2.Y * _matrix2._2.Z) + (_matrix1._2.Z * _matrix2._3.Z);

	//Row 3
	Row3.X = (_matrix1._3.X * _matrix2._1.X) + (_matrix1._3.Y * _matrix2._2.X) + (_matrix1._3.Z * _matrix2._3.X);
	Row3.Y = (_matrix1._3.X * _matrix2._1.Y) + (_matrix1._3.Y * _matrix2._2.Y) + (_matrix1._3.Z * _matrix2._3.Y);
	Row3.Z = (_matrix1._3.X * _matrix2._1.Z) + (_matrix1._3.Y * _matrix2._2.Z) + (_matrix1._3.Z * _matrix2._3.Z);

	temp = { Row1, Row2, Row3 };
	return temp;
}

Vertex MultiplyMatrixVertex(Matrix _matrix, Vertex _vertex)
{
	Vertex temp;

	/*Multiplication Logic*/
	temp.X = (_matrix._1.X * _vertex.X) + (_matrix._2.X * _vertex.Y) + (_matrix._3.X * _vertex.Z);
	temp.Y = (_matrix._1.Y * _vertex.X) + (_matrix._2.Y * _vertex.Y) + (_matrix._3.Y * _vertex.Z);
	temp.Z = (_matrix._1.Z * _vertex.X) + (_matrix._2.Z * _vertex.Y) + (_matrix._3.Z * _vertex.Z);
	
	return temp;
}

Vertex NdcToScreen(Vertex _vertex)
{
	Vertex temp;

	float X = _vertex.X + 1;
	float Y = 1 - _vertex.Y;
	//float Z = _vertex.Z + 1;

	X = X * (RasterWidth / 2);
	Y = Y * (RasterHeight / 2);
	//Z = Z * (RasterWidth / 2);

	temp.X = X;
	temp.Y = Y;
	//temp.Z = Z;

	return temp;
}

Matrix MatrixZRotate(float _radian)
{
	Matrix temp;

	temp._1 = { cos(_radian), -sin(_radian), 0, 0 };
	temp._2 = { sin(_radian), cos(_radian), 0, 0 };
	temp._3 = { 0, 0, 1, 0};
	temp._4 = { 0,0,0,1};

	return temp;
}