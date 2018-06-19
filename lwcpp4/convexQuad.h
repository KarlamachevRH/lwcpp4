#pragma once
#include "shape.h"

class convexQuad :public shape
{
	template <class Type> friend class doubleLinkedList;
protected:
	double *diagonal1, *diagonal2; //диагонали выпуклого четырехугольника
	double *angle; //угол между диагоналями			
	double *diagonal1Angle; //угол между осью х и диагональю 1
	int mark; //признак, по которому фигуры делятся на категории и заносятся в таблицу-контейнер

public:
	convexQuad(); //конструктор по умолчанию
	convexQuad(double d1, double d2, double angle);  // конструктор с заданными параметрами
	convexQuad(convexQuad &q);  //конструктор копирования
	~convexQuad(); //деструктор

	double Get_diagonal1(); //получить значение
	double Get_diagonal2();
	double Get_angle();
	double Get_diagonal1Angle();
	double Get_mark();

	void Set_diagonal1(double d1); // изменить значение
	void Set_diagonal2(double d2);
	void Set_angle(double h);
	void Set_diagonal1Angle(double d1A);
	void Set_mark(double m);

	void ReadFile();//считать из файла
	void SaveFile();//сохранить в файл

	void PrintWindowSize(HDC hdc, HWND hwnd, char *buf);// вывод размера окна

	void Draw(HDC hdc);//переопределение чисто виртуальной функции

	double GetNewAngle(RECT &rt, HWND hwnd); //задать новые размеры фигуры
	double GetNewD1(RECT rt, HWND hwnd);
	double GetNewD2(RECT rt, HWND hwnd);

	void SetNewSize(double a, double d1, double d2); //изменить размеры фигуры
	int GetNewPositionX(); //получить величину смещения по оси х
	int GetNewPositionY(); //получить величину смещения по оси y
	void SetNewPosition(int coeffX, int coeffY, HWND hwnd); // изменить положение фигуры
};