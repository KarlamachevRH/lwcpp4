#pragma once
#include <cstdio>
#include <tchar.h>
#include <iostream>
#include <fstream>
#include <windows.h>
#include <windowsx.h>
#include <conio.h>
#include <cmath>

using namespace std;

class shape
{
protected:
	int *x, *y;

public:
	virtual void Draw(HDC hdc) = 0; // чисто виртуальная функция
};

