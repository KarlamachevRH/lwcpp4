#include "convexQuad.h"


convexQuad::convexQuad()
{
	diagonal1 = new double;
	diagonal2 = new double;
	angle = new double;
	diagonal1Angle = new double;
	x = new int;
	y = new int;
	*x = 100;
	*y = 100;
	*diagonal1 = 280.0;
	*diagonal2 = 260.0;
	*angle = 90.0;
	*diagonal1Angle = 45.0;
	mark = 1;
}

convexQuad::convexQuad(double d1, double d2, double angle)
{
	diagonal1 = new double;
	diagonal2 = new double;
	this->angle = new double;
	this->diagonal1Angle = new double;
	x = new int;
	y = new int;
	*x = 100;
	*y = 100;
	*diagonal1 = d1;
	*diagonal2 = d2;
	*this->angle = angle;
	*this->diagonal1Angle = 45.0;	
	if (d1 < d2) mark = 0;
	else if (d1 > d2) mark = 1;
	else if (d1 == d2) mark = 2;
}

convexQuad::convexQuad(convexQuad &q)
{
	diagonal1 = new double;
	diagonal2 = new double;
	angle = new double;
	diagonal1Angle = new double;
	*diagonal1 = *q.diagonal1; // копирование атрибутов экзмепляра класса
	*diagonal2 = *q.diagonal2;
	*angle = *q.angle;
	*diagonal1Angle = *q.diagonal1Angle;
	mark = q.mark;
}

convexQuad::~convexQuad()
{
	delete x;
	delete y;
	delete diagonal1;
	delete diagonal2;
	delete angle;
	delete diagonal1Angle;
}

//получение значений элементов данных класса
double convexQuad::Get_diagonal1() { return *diagonal1; }
double convexQuad::Get_diagonal2() { return *diagonal2; }
double convexQuad::Get_angle() { return *angle; }
double convexQuad::Get_diagonal1Angle() { return *angle; }
double convexQuad::Get_mark() { return *angle; }

//инициализация элементов данных класса
void convexQuad::Set_diagonal1(double d1) { *diagonal1 = d1; }
void convexQuad::Set_diagonal2(double d2) { *diagonal2 = d2; }
void convexQuad::Set_angle(double angle) { *this->angle = angle; }
void convexQuad::Set_diagonal1Angle(double d1A) { *this->diagonal1Angle = d1A; }
void convexQuad::Set_mark(double m) { this->mark = mark; }

void convexQuad::ReadFile()
{
	double diagonal1;
	double diagonal2;
	double angle;
	ifstream fin("ConvexQuad.txt");
	if (!fin.is_open()) throw 1; //если файл не может быть открыт выбросить код ошибки

	fin >> diagonal1;
	fin >> diagonal2;
	fin >> angle;

	Set_diagonal1(diagonal1);
	Set_diagonal2(diagonal2);
	Set_angle(angle);

	fin.close(); // закрыть файл	
}

void convexQuad::SaveFile()
{
	ofstream fout("ConvexQuad.txt"); // открыть файл

	fout << Get_diagonal1() << " ";
	fout << Get_diagonal2() << " ";
	fout << Get_angle() << endl;

	fout.close();
	cout << "Файл записан\n" << endl;
}

void convexQuad::PrintWindowSize(HDC hdc, HWND hwnd, char *buf)
{
	RECT rt;
	// получаем размер окна
	GetClientRect(hwnd, &rt);
	// устанавливаем цвет фона
	SetBkColor(hdc, RGB(0, 0, 0));
	// устанавливаем цвет текста
	SetTextColor(hdc, RGB(202, 120, 186));
	// формируем выводимую строку
	sprintf_s(buf, 100, "Размер окна %d на %d пикселей", rt.right, rt.bottom);
	// выводим строку графическими средствами
	TextOutA(hdc, 10, 10, buf, (int)strlen(buf));
}

void convexQuad::Draw(HDC hdc)
{
	double diagonal1 = Get_diagonal1();
	double diagonal2 = Get_diagonal2();
	double angle = Get_angle();
	double PI = 3.14159265;
	double deg = PI / 180; // 1 градус в радианах
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
}

double convexQuad::GetNewAngle(RECT & rt, HWND hwnd)
{
	GetClientRect(hwnd, &rt);
	double a;
	double angleMax = 120;
	cout << "Введите значение угла между диагоналями выпуклого четырехугольника" << endl
		<< ">:";
	cin >> a;
	if (a <= 30 || a >= angleMax) throw 1;
	return a;	
}

double convexQuad::GetNewD1(RECT rt, HWND hwnd)
{
	GetClientRect(hwnd, &rt);
	double d1;
	double PI = 3.14159265;
	double deg = PI / 180;
	cout << "Введите длину диагонали 1" << endl
		<< ">:";
	cin >> d1;

	if (d1<10 || d1>(rt.right*cos(*diagonal1Angle * deg) - *x*sqrt(2))) throw 1;
	return d1;
}

double convexQuad::GetNewD2(RECT rt, HWND hwnd)
{
	GetClientRect(hwnd, &rt);
	double d2;
	double angle = Get_angle();
	double PI = 3.14159265;
	double deg = PI / 180;
	cout << "Введите длину диагонали 2" << endl
		<< ">:";
	cin >> d2;

	if (d2 < 10 || d2 * cos((angle - *diagonal1Angle) * deg) > rt.right - *x || d2 * sin((angle - *diagonal1Angle) * deg) > rt.bottom - *y) throw 1;
	return d2;
}

void convexQuad::SetNewSize(double a, double d1, double d2)
{
	Set_diagonal1(d1);
	Set_diagonal2(d2);
	Set_angle(a);
}

int convexQuad::GetNewPositionX()
{
	int coeffX;
	cout << "Задайте смещение по оси х" << endl
		<< ">:";
	cin >> coeffX;
	return coeffX;
}

int convexQuad::GetNewPositionY()
{
	int coeffY;
	cout << "Задайте смещение по оси y" << endl
		<< ">:";
	cin >> coeffY;
	return coeffY;
}

void convexQuad::SetNewPosition(int coeffX, int coeffY, HWND hwnd)
{
	RECT rt;
	GetClientRect(hwnd, &rt);
	*x += coeffX;
	*y += coeffY;
	if (*x <= 0 || *x>rt.right) throw 1;
	if (*y <= 0 || *y>rt.bottom) throw 1;
}