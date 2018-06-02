#include "filledConvexQuad.h"

filledConvexQuad::filledConvexQuad() :convexQuad()
{
}

filledConvexQuad::filledConvexQuad(double d1, double d2, double angle): convexQuad(d1, d2, angle) //вызов конструктора базового класса
{
}

filledConvexQuad::filledConvexQuad(filledConvexQuad &f): convexQuad(f)
{
}

filledConvexQuad::~filledConvexQuad()
{
}

void filledConvexQuad::Draw(HDC hdc)
{
	double diagonal1 = Get_diagonal1();
	double diagonal2 = Get_diagonal2();
	double angle = Get_angle();
	double PI = 3.14159265;
	double deg = PI / 180; // 1 градус в радианах
	HBRUSH hSomeBrush = SetBrush(hdc); //выбрать кисть для заливки
	HBRUSH hOldBrush = SelectBrush(hdc, hSomeBrush);

	//вычисление координат точек для построения выпуклого четырехугольника с внесением данных в массив структур
	POINT ppt[4] = { { *x,
		*y },
	{ *x + lround((diagonal1 / 2) * cos(*diagonal1Angle * deg) + (diagonal2 * 5 / 8)*cos((angle - *diagonal1Angle) * deg)),
		*y + lround((diagonal1 / 2) * cos(*diagonal1Angle * deg) - (diagonal2 * 5 / 8) * sin((angle - *diagonal1Angle) * deg)) },
	{ *x + lround(diagonal1 * cos(*diagonal1Angle * deg)),
		*y + lround(diagonal1 * sin(*diagonal1Angle * deg)) },
	{ *x + lround((diagonal1 / 2) * sin(*diagonal1Angle * deg) - (diagonal2 * 3 / 8)*cos((angle - *diagonal1Angle)*deg)),
		*y + lround((diagonal1 / 2) * cos(*diagonal1Angle * deg) + (diagonal2 * 3 / 8) * sin((angle - *diagonal1Angle)*deg)) } };
	// рисуем выпуклый четырехугольник
	Polygon(hdc, ppt, 4);

	DelBrush(hdc, hSomeBrush, hOldBrush); //удалить кисть для заливки
}
