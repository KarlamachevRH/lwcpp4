#include "doubleLinkedList.h"

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
			<< "8. В меню работы с контейнером для фигур\n"
			<< "9. Выход\n"
			<< "ESC для повтора выбора пункта меню\n"
			<< ">:";
		cin >> choice;
	} while (choice < 1 || choice > 9);
	return choice;
}

//меню выбора действий при работе с контейнером
int menuContainers()
{
	int choice = 0;
	do
	{
		cout << "Введите номер пункта меню выбора действий при работе с контейнерами:\n"
			<< "1. Добавить объект в контейнер - таблицу\n"
			<< "2. Загрузить данные объектов из файла в контейнер - таблицу \n"
			<< "3. Сохранить данные объектов из контейнера в файл\n"
			<< "4. Удалить элемент из таблицы\n"
			<< "5. Вывод данных объектов в таблице на экран\n"
			<< "6. Выход в меню выбора типа контейнера\n"
			<< "ESC для повтора выбора пункта меню\n"
			<< ">:";
		cin >> choice;
	} while (choice < 1 || choice > 6);

	return choice;
}

template <typename Type> 
Type *createShapeFirstTime()
{
	Type *q = new Type();	
	return q;
}

template <typename Type> 
Type *createShape()
{
	double d1, d2, angle;
	cout << "Введите параметры фигуры: d1, d2, angle\n";
	cin >> d1 >> d2 >> angle;
	Type *q = new Type(d1, d2, angle);	
	return q;
}

//работа с двухсвязным списком
void workingWithDoubleLinkedList()
{
	doubleLinkedList <convexQuad> *l1= new doubleLinkedList <convexQuad>(); //создание объекта-контейнера
	doubleLinkedList <filledConvexQuad> *l2 = new doubleLinkedList <filledConvexQuad>();
	doubleLinkedList <combinedConvexQuad> *l3 = new doubleLinkedList <combinedConvexQuad>();
	
	int cnt = 0; //счетчик циклов основного меню в функции

	while (1)
	{
		//выбор действий при работе с контейнером
		int choice = menuContainers();

		convexQuad *p = NULL;
		filledConvexQuad *p1 = NULL;
		combinedConvexQuad *p2 = NULL;

		//начальное создание объекта - фигуры
		if (cnt == 0)
		{
			p = createShapeFirstTime<convexQuad>();
			p1 = createShapeFirstTime<filledConvexQuad>();
			p2 = createShapeFirstTime<combinedConvexQuad>();
		}

		//добавить еще одну фигуру
		if (cnt > 0 && choice == 1)
		{
			p = createShape<convexQuad>();
			p1 = createShape<filledConvexQuad>();
			p2 = createShape<combinedConvexQuad>();
		}

		switch (choice)
		{
		case 1: l1->addShapeToTable(p);
			l2->addShapeToTable(p1);
			l3->addShapeToTable(p2);
			cout << "Данные фигур добавлены в контейнер" << endl;
			break;

		case 2:	try
		{
			l1->writeDataFromFileToTable();
			l2->writeDataFromFileToTable();
			l3->writeDataFromFileToTable();

			cout << "Данные из файла добавлены в таблицы-контейнеры" << endl;
		}
				catch (int error)
				{
					if (error == 1)
					{
						cout << "Файл не найден" << endl;
					}
				}
				break;

		case 3: l1->saveDataInTableToFile();
			cout << "Данные в контейнере сохранены в файл" << endl;
			break;

		case 4: l1->deleteTableElement();
			cout << "Фигура удалена из таблицы-контейнера" << endl;
			break;

		case 5: 
			cout << "Фигура-контур:" << endl;
			l1->showAllListsElements();
			cout << "Закрашенная фигура:" << endl;
			l2->showAllListsElements();
			cout << "Выпуклый четырехугольник с вложенной фигурой:" << endl;
			l3->showAllListsElements();
			break;

		case 6: delete l1;
			delete l2;
			delete l3;
			return;
			break;

		default: break;
		}
		cnt++;
	}
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

		shape *pS;
		convexQuad *q = new convexQuad(280.0, 260.0, 90);
		filledConvexQuad *f = new filledConvexQuad(280.0, 260.0, 90);
		combinedConvexQuad *c = new combinedConvexQuad(280.0, 260.0, 90);

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
				pS = q; pS->Draw(hdc);// механизм позднего связывания в построенной	иерархии классов
			} while (_getch() != 27);
			break;

			case 3:	do
			{				
				pS = f; pS->Draw(hdc);
			} while (_getch() != 27);
			break;

			case 4: do
			{				
				pS = c; pS->Draw(hdc);
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

			case 8:	workingWithDoubleLinkedList();
				break;

			case 9:	delete q;
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