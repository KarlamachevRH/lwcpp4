#pragma once
#include "filledConvexQuad.h"

class combinedConvexQuad :public filledConvexQuad
{
public:
	combinedConvexQuad();
	combinedConvexQuad(double d1, double d2, double angle);
	combinedConvexQuad(combinedConvexQuad &c);
	~combinedConvexQuad();

	void Draw(HDC hdc); //переопределение чисто виртуальной функции	
};

