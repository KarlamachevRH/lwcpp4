#pragma once
#include "filledConvexQuad.h"

class combinedConvexQuad :public filledConvexQuad
{
protected:
	filledConvexQuad *f; //внешняя фигура

public:
	combinedConvexQuad();
	combinedConvexQuad(double d1, double d2, double angle, filledConvexQuad *f);
	combinedConvexQuad(combinedConvexQuad &c);
	~combinedConvexQuad();

	void Draw(HDC hdc); //переопределение чисто виртуальной функции
	void DrawFigureInside(HDC hdc); //отрисовка вложенной фигуры
};

