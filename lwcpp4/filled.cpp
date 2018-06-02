#include "filled.h"

int filled::SetBrushColour()
{
	int choice;
	cout << "Введите номер желаемого цвета заливки фигуры:\n"
		<< "1. Красный\n"
		<< "2. Зеленый\n"
		<< "3. Синий\n"
		<< ">:";
	cin >> choice;
	return choice;	
}

HBRUSH filled::SetBrush(HDC hdc)
{
	HBRUSH hSomeBrush = 0;
	int choice = SetBrushColour();
	switch (choice)
	{
	case 1: hSomeBrush = CreateSolidBrush(RGB(250, 30, 65)); //красный
		break;

	case 2: hSomeBrush = CreateSolidBrush(RGB(90, 250, 80)); //зеленый
		break;

	case 3: hSomeBrush = CreateSolidBrush(RGB(90, 80, 250)); //синий
		break;
	}
	return hSomeBrush;
}

void filled::DelBrush(HDC hdc, HBRUSH hSomeBrush, HBRUSH hOldBrush)
{
	DeleteBrush(hSomeBrush);
	hOldBrush = SelectBrush(hdc, hOldBrush);
}

