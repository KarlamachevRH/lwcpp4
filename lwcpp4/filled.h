#pragma once
#include "convexQuad.h"

class filled
{
public:	
	int SetBrushColour(); // выбор цвета кисти для заливки
	HBRUSH SetBrush(HDC hdc); //выбор кисти для заливки
	void DelBrush(HDC hdc, HBRUSH hSomeBrush, HBRUSH hOldBrush); //удалить кисть
};

