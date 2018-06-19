#pragma once
#include "convexQuad.h"

class filled
{
	template <class Type> friend class doubleLinkedList;
public:	
	int SetBrushColour(); // выбор цвета кисти для заливки
	HBRUSH SetBrush(HDC hdc); //выбор кисти для заливки
	void DelBrush(HDC hdc, HBRUSH hSomeBrush, HBRUSH hOldBrush); //удалить кисть
};