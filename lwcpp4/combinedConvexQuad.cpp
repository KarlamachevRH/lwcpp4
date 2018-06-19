#include "combinedConvexQuad.h"

combinedConvexQuad::combinedConvexQuad() :filledConvexQuad()
{	
}

combinedConvexQuad::combinedConvexQuad(double d1, double d2, double angle) :filledConvexQuad(d1, d2, angle)
{	
}

combinedConvexQuad::combinedConvexQuad(combinedConvexQuad &c) : filledConvexQuad(c)
{	
}

combinedConvexQuad::~combinedConvexQuad()
{	
}

void combinedConvexQuad::Draw(HDC hdc)
{
	filledConvexQuad::Draw(hdc);
	double diagonal1 = Get_diagonal1();
	double diagonal2 = Get_diagonal2();
	double angle = Get_angle();
	double PI = 3.14159265;
	double deg = PI / 180;
	int c = 25; // коэффициент для внутреннего расположения прямоугольника относительно основной фигуры
	Rectangle(hdc, *x + c * 3, *y + c * 2, *x + lround(diagonal1 * cos(*diagonal1Angle * deg)) - c * 2, *y + lround(diagonal1 * sin(*diagonal1Angle * deg) - c * 2));
}