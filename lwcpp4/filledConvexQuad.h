#pragma once
#include "filled.h"

class filledConvexQuad :public convexQuad, public filled
{
	template <class Type> friend class doubleLinkedList;
public:
	filledConvexQuad(); 
	filledConvexQuad(double d1, double d2, double angle);
	filledConvexQuad(filledConvexQuad &f);
	~filledConvexQuad();
	
	void Draw(HDC hdc);//переопределение чисто виртуальной функции
};