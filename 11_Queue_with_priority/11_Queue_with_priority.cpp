#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <windows.h>
using namespace std;

template <typename T>
class Queue
{
	T* elements;
	int count;
public:
	Queue() : elements(nullptr), count(0) {}
	~Queue()
	{
		if (elements != nullptr)
		{
			delete[] elements;
		}
	}
	void Enqueue(T el)
	{
		T* temp = new T[count + 1];
		for (int i = 0; i < count; i++)
		{
			temp[i] = elements[i];
		}
		temp[count] = el;
		if (elements != nullptr)
		{
			delete[] elements;
		}
		elements = temp;
		count++;
	}
	bool IsEmpty() const
	{
		return count == 0;
	}
	T Dequeue()
	{
		if (!IsEmpty())
		{
			T first = elements[0];
			for (int i = 0; i < count - 1; i++)
			{
				elements[i] = elements[i + 1];
			}
			count--;
			return first;
		}
		return T();
	}
	T Front() const
	{
		if (!IsEmpty())
		{
			return elements[0];
		}
		return T();
	}
};

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	srand(time(0));
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD w;

	// ? ? ? ? ?
	wchar_t sym[5] = { L'\u2665', L'\u2666', L'\u2663', L'\u2660', L'\u263B' };
	// кольори: 12 - червоний, 11 - блакитний, 10 - зелений, 15 - білий, 14 - жовтий
	int col[5] = { 12, 11, 10, 15, 14 };

	Queue<int> d[3];
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			d[i].Enqueue((j + i * 2) % 5);
		}
	}

	int balance = 100;
	int bet = 10;
	int key;

	cout << "ОДНОРУКИЙ БАНДИТ" << endl;
	cout << "Пробіл - крутити" << endl;
	cout << "Enter - вийти" << endl << endl;

	while (balance >= bet)
	{
		key = _getch();
		if (key == 13)
		{
			break;
		}
		if (key != 32)
		{
			continue;
		}
		balance -= bet;

		for (int i = 0; i < 3; i++)
		{
			int n = rand() % 16 + 5;
			for (int j = 0; j < n; j++)
			{
				d[i].Enqueue(d[i].Dequeue());
			}
		}

		int a = d[0].Front();
		int b = d[1].Front();
		int c = d[2].Front();
		int x[3] = { a, b, c };

		cout << "[ ";
		for (int i = 0; i < 3; i++)
		{
			SetConsoleTextAttribute(h, col[x[i]]);
			WriteConsoleW(h, &sym[x[i]], 1, &w, NULL);
			SetConsoleTextAttribute(h, 7);
			if (i < 2)
			{
				cout << " | ";
			}
		}
		cout << " ]" << endl;

		if (a == b)
		{
			if (b == c)
			{
				int win = 50;
				if (a == 4)
				{
					win = 200;
				}
				balance += win;
				cout << "!!! ДЖЕКПОТ !!! : " << win << endl;
			}
			else
			{
				balance += 20;
				cout << "Два однакових, виграш: 20" << endl;
			}
		}
		else if (b == c)
		{
			balance += 20;
			cout << "Два однакових, виграш: 20" << endl;
		}
		else if (a == c)
		{
			balance += 20;
			cout << "Два однакових, виграш: 20" << endl;
		}
		else
		{
			cout << "Програш: 0" << endl;
		}

		cout << "Ваш баланс: " << balance << endl << endl;
	}

	cout << "Гру завершено!" << endl;
	cout << "Дякуємо за гру! Ви маєте: " << balance << endl;
} 