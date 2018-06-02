#include "combinedConvexQuad.h"

combinedConvexQuad::combinedConvexQuad() :filledConvexQuad()
{
	f = new filledConvexQuad;
}

combinedConvexQuad::combinedConvexQuad(double d1, double d2, double angle, filledConvexQuad *f) :filledConvexQuad(d1, d2, angle)
{
	this->f = f;
}

combinedConvexQuad::combinedConvexQuad(combinedConvexQuad &c) : filledConvexQuad(c)
{
	this->f = c.f;
}

combinedConvexQuad::~combinedConvexQuad()
{
	delete f;
}

void combinedConvexQuad::Draw(HDC hdc)
{
	f->Draw(hdc);
	DrawFigureInside(hdc);
}

void combinedConvexQuad::DrawFigureInside(HDC hdc)
{
	double diagonal1 = Get_diagonal1();
	double diagonal2 = Get_diagonal2();
	double angle = Get_angle();
	double PI = 3.14159265;
	double deg = PI / 180;
	int c = 25; // коэффициент для внутреннего расположения прямоугольника относительно основной фигуры
	Rectangle(hdc, *x + c*3, *y + c*2, *x + lround(diagonal1 * cos(*diagonal1Angle * deg)) - c*2, *y + lround(diagonal1 * sin(*diagonal1Angle * deg) - c*2));
}