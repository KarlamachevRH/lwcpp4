#include "combinedConvexQuad.h"

using namespace std;

//основное меню
int mainMenu()
{
	// Варианты меню
	int choice;
	do
	{
		cout << "Введите номер пункта меню:\n"
			<< "1. Ввод сохраненных данных из файла\n"
			<< "2. Вывод выпуклого четырехугольника\n"
			<< "3. Вывод закрашенного выпуклого четырехугольника\n"
			<< "4. Вывод фигуры внутри выпуклого четырехугольника\n"
			<< "5. Изменение размеров фигуры\n"
			<< "6. Перемещение фигуры\n"
			<< "7. Вывод данных в файл\n"
			<< "8. Выход\n"			
			<< "ESC для повтора выбора пункта меню\n"
			<< ">:";
		cin >> choice;
	} while (choice < 1 || choice > 8);
	return choice;
}

//функция проверки наличия окна блокнота
bool isFinded(HWND hwnd)
{
	bool f = false;
	if (hwnd != NULL)
	{
		f = true;
		cout << "Окно блокнота найдено\n";
		TCHAR name[200];
		GetWindowText(hwnd, name, sizeof(name));
		wcout << name << endl;
	}
	else

	{
		cout << "Окно блокнота не найдено\n";
		f = false;
		cin.get();
	}
	return f;
}

int main()
{
	setlocale(LC_ALL, "rus");

	double a, d1, d2; //переменные задания новых размеров
	int coeffX, coeffY; //переменные задания смещения по осям x и y
	int err = 0;
	HWND hwnd = FindWindow(TEXT("Notepad"), NULL);
	if (isFinded(hwnd))
	{
		// получаем контекст отображения
		HDC hdc = GetDC(hwnd);
		RECT rt;
		char buf[100];		
		HPEN hBluePen = CreatePen(PS_SOLID, 5, RGB(223, 238, 94));
		HPEN hOldPen = SelectPen(hdc, hBluePen);

		convexQuad *q = new convexQuad(280.0, 260.0, 90);
		filledConvexQuad *f = new filledConvexQuad(280.0, 260.0, 90);
		combinedConvexQuad *c = new combinedConvexQuad(280.0, 260.0, 90, f);

		while (1)
		{
			int choice = mainMenu();

			q->PrintWindowSize(hdc, hwnd, buf);
			switch (choice)
			{
			case 1: try
			{
				q->ReadFile();
				f->ReadFile();
				c->ReadFile();
				cout << "Данные загружены" << endl;
			}
					catch (int error)
					{
						if (error == 1)
						{
							cout << "Файл не найден" << endl;
						}
					}
					break;

			case 2:	do
			{
				q->Draw(hdc);
			} while (_getch() != 27);
			break;

			case 3:	do
			{				
				f->Draw(hdc);				
			} while (_getch() != 27);
			break;

			case 4: do
			{				
				c->Draw(hdc);				
			} while (_getch() != 27);
			break;

			case 5: do
			{
				err = 0;
				try
				{
					a = q->GetNewAngle(rt, hwnd);
					d1 = q->GetNewD1(rt, hwnd);
					d2 = q->GetNewD2(rt, hwnd);
				}
				catch (int error)
				{
					if (error == 1)
					{
						cout << "Введенные данные не корректны, повторите ввод" << endl;
						err = error;
					}
				}
			} while (err == 1);
			q->SetNewSize(a, d1, d2);
			break;

			case 6:	
				do
				{
					err = 0;
					try
					{
						coeffX = q->GetNewPositionX();
						coeffY = q->GetNewPositionY();
						q->SetNewPosition(coeffX, coeffY, hwnd);
					}
					catch (int error)
					{
						if (error == 0)
						{
							cout << "Введенные данные не корректны, повторите ввод" << endl;
							err = error;
						}
					}
				} while (err == 1);
				break;

			case 7:	q->SaveFile();
				break;

			case 8:	delete q;
				delete c;
				ReleaseDC(hwnd, hdc);
				return 0;
				break;				

			default: break;
			}
		}
	}
	else return -1;
}