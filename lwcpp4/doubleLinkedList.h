#pragma once
#include "combinedConvexQuad.h"

//класс - контейнер - двунаправленный список
template <class Type> 
class doubleLinkedList
{
	class CNode
	{
	public:
		int key;
		Type *quads[5]; //массив для хранения объектов - фигур		
		CNode *next;
		CNode *prev;
		CNode()
		{
			key = 0;			
			next = NULL;
			prev = NULL;
			for (int i = 0; i < 5; i++)
			{
				quads[i] = NULL;
			}
		}
		~CNode()
		{
			for (int i = 0; i < 5; i++)
			{
				if (quads[i] != NULL) delete quads[i];
			}
		}
	};
	CNode *head;
	CNode *tail;
	CNode *curr;
public:
	doubleLinkedList();
	void addShapeToTable(Type *paintQuad);
	void searchNode(int mark);
	int searchFreeCell();
	void createNode(int mark);
	void deleteTableElement(); //удаление фигуры в таблице
	void deleteShape();
	void showAllListsElements();
	void showOneListElements(Type *tmp);
	void showFromHead(Type *tmp);
	void showFromTail(Type *tmp);
	void saveDataInTableToFile();
	void writeDataFromFileToTable();
	~doubleLinkedList();
};

template <class Type>
doubleLinkedList<Type>::doubleLinkedList() 
{
	head = NULL;
	tail = NULL;
	curr = NULL;
}

template <class Type>
void doubleLinkedList<Type>::addShapeToTable(Type *paintQuad)
{
	createNode(paintQuad->mark);
	if (searchFreeCell() >= 0) curr->quads[searchFreeCell()] = paintQuad;
	else cout << "Нет свободных ячеек, нажмите любую кнопку для возврата" << endl;	
}

template <class Type>
void doubleLinkedList<Type>::searchNode(int mark)
{
	curr = head;
	while (curr != NULL)
	{
		if (curr->key == mark)
			return;
		curr = curr->next;
	}
}

template <class Type>
int doubleLinkedList<Type>::searchFreeCell()
{
	for (int i = 0; i < 5; i++)
	{
		if (curr->quads[i] == NULL) return i;
	}
	return -1;
}

template <class Type>
void doubleLinkedList<Type>::createNode(int mark)
{
	CNode *node;
	node = new CNode;
	if (head == NULL)
	{
		head = tail = curr = node;
		curr->key = mark;
	}
	else
	{
		curr = head;
		while (curr->key != mark && curr->next != NULL)
		{
			curr = curr->next;
		}
		if (curr->key == mark)
		{
			delete node;
		}
		else
		{
			curr->next = node;
			node->prev = curr;
			curr = tail = node;
			curr->key = mark;
		}
	}
}

template <class Type>
void doubleLinkedList<Type>::deleteTableElement()
{
	int mark;
	if (head == NULL)
	{
		cout << "Таблица пуста" << endl;
		return;
	}
	cout << "Введите идентификатор удаляемых фигур:\n"
		<< "Если d1 < d2 - цифра 0\n"
		<< "Если d1 > d2 - цифра 1\n"
		<< "Если d1 = d2 - цифра 2" << endl;
	do {
		cin >> mark;
	} while (mark < 0 && mark > 2);
	searchNode(mark);
	deleteShape();
}

template <class Type>
void doubleLinkedList<Type>::deleteShape()
{
	int choice;
	cout << "Введите номер удаляемой фигуры 0...4: " << endl;
	do {
		cin >> choice;
		if (curr->quads[choice] == NULL)
		{
			cout << "Такой фигуры нет в контейнере\n";
			return;
		}
	} while (choice < 0 && choice > 4);

	delete curr->quads[choice];
	curr->quads[choice] = NULL;
}


//распечатка элементов в таблице
template <class Type>
void doubleLinkedList<Type>::showAllListsElements()
{
	if (head != NULL)
	{
		Type *tmp;
		tmp = NULL;
		int choice;
		cout << "Выберите направление вывода данных объектов списка:\n"
			<< "1 - c произвести вывод с начала списка\n"
			<< "2 - с конца списка" << endl;
		do {
			cin >> choice;
		} while (choice < 1 && choice > 2);

		switch (choice)
		{
		case 1: showFromHead(tmp);
			break;
		case 2: showFromTail(tmp);
			break;
		}
	}
	else cout << "Нет данных в таблице" << endl
		<< "Нажмите Esc для возврата" << endl;
}

template <class Type>
void doubleLinkedList<Type>::showOneListElements(Type *tmp)
{
	for (int i = 0; i < 5; i++)
	{
		while (curr->quads[i] == NULL && i<5) i++;
		if (i == 5)i--;
		if (curr->quads[i] != NULL)
		{
			tmp = curr->quads[i];
			cout << "Номер фигуры: " << i << endl
				<< "Длина диагонали 1 выпуклого четырехугольника: " << tmp->Get_diagonal1() << endl
				<< "Длина диагонали 2 выпуклого четырехугольника: " << tmp->Get_diagonal2() << endl
				<< "Величина угла между диагоналями выпуклого четырехугольника: " << tmp->Get_angle() << endl;
		}
	}
}

template <class Type>
void doubleLinkedList<Type>::showFromHead(Type *tmp)
{
	curr = head;
	while (curr != NULL)
	{
		cout << "Номер категории фигур: " << curr->key << endl;
		showOneListElements(tmp);
		curr = curr->next;
	}
}

template<class Type>
void doubleLinkedList<Type>::showFromTail(Type * tmp)
{
	curr = tail;
	while (curr != NULL)
	{
		cout << "Номер категории фигур: " << curr->key << endl;
		showOneListElements(tmp);
		curr = curr->prev;
	}
}

template <class Type>
void doubleLinkedList<Type>::saveDataInTableToFile()
{
	if (head != NULL)
	{
		Type *tmp = NULL;
		ofstream fout("DoubleLinkedListTable.txt");
		curr = head;
		while (curr != NULL)
		{
			fout << curr->key << " ";
			for (int i = 0; i < 5; i++)
			{
				while (curr->quads[i] == NULL && i<5) i++;
				if (i == 5)i--;
				if (curr->quads[i] != NULL)
				{
					tmp = curr->quads[i];
					fout << tmp->Get_diagonal1() << " "
						<< tmp->Get_diagonal2() << " "
						<< tmp->Get_angle() << endl;
				}
			}
			curr = curr->next;
		}
	}
	else cout << "Нет данных в таблице" << endl
		<< "Нажмите Esc для возврата" << endl;
}

template <class Type>
void doubleLinkedList<Type>::writeDataFromFileToTable()
{
	Type *tmp = NULL;
	double d1, d2, angle;
	ifstream fin("DoubleLinkedListTable.txt");
	if (!fin.is_open()) throw 1;
	while (fin.peek() != EOF)
	{
		int mark;
		fin >> mark;
		createNode(mark);
		for (int i = 0; fin.peek() != '\n' && i < 5; i++)
		{
			tmp = new Type();
			curr->quads[i] = tmp;
			fin >> d1;
			fin >> d2;
			fin >> angle;
			tmp->Set_diagonal1(d1);
			tmp->Set_diagonal2(d2);
			tmp->Set_angle(angle);
			if (fin.peek() == EOF) i = 5;
		}
	}
	fin.close();
}

template <class Type>
doubleLinkedList<Type>::~doubleLinkedList()
{
	while (head)
	{
		curr = head->next;
		delete head;
		head = curr;
	}
}