#include <iostream>
#include <string>
#include <windows.h>
using namespace std;

struct Document
{
	string name;
	int priority;
	string position;
	void Print()
	{
		cout << name << " (" << position << ", пріоритет " << priority << ")";
	}
};

template <typename T>
class QueueWithPriority
{
	T* elements;
	int count;
public:
	QueueWithPriority() : elements(nullptr), count(0) {}
	~QueueWithPriority()
	{
		if (elements != nullptr)
		{
			delete[] elements;
		}
	}
	void Enqueue(T el)
	{
		int index = 0;
		while (index < count && elements[index].priority >= el.priority)
		{
			index++;
		}
		T* temp = new T[count + 1];
		for (int i = 0; i < index; i++)
		{
			temp[i] = elements[i];
		}
		temp[index] = el;
		for (int i = index; i < count; i++)
		{
			temp[i + 1] = elements[i];
		}
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
	void Print()
	{
		cout << "------------------ Черга -------------" << endl;
		for (int i = 0; i < count; i++)
		{
			cout << i + 1 << ") ";
			elements[i].Print();
			cout << endl;
		}
		cout << "__________________________________" << endl;
	}
};

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	QueueWithPriority<Document> q;
	int choice = -1;
	while (choice != 0)
	{
		cout << "1 - Додати документ" << endl;
		cout << "2 - Виконати друк" << endl;
		cout << "3 - Показати чергу" << endl;
		cout << "0 - Вихід" << endl;
		cout << "Ваш вибір: ";
		cin >> choice;

		if (choice == 1)
		{
			Document d;
			cout << "Ім'я файлу: ";
			cin >> d.name;
			cout << "1 - Гість" << endl;
			cout << "2 - Адміністратор" << endl;
			cout << "3 - Менеджер" << endl;
			cout << "4 - Директор" << endl;
			cout << "Ваша посада: ";
			cin >> d.priority;
			if (d.priority == 1)
			{
				d.position = "Гість";
			}
			else if (d.priority == 2)
			{
				d.position = "Адміністратор";
			}
			else if (d.priority == 3)
			{
				d.position = "Менеджер";
			}
			else if (d.priority == 4)
			{
				d.position = "Директор";
			}
			else
			{
				cout << "Невірна посада" << endl;
				continue;
			}
			q.Enqueue(d);
			cout << "Документ додано в чергу" << endl;
		}
		else if (choice == 2)
		{
			if (q.IsEmpty())
			{
				cout << "Черга порожня" << endl;
			}
			else
			{
				cout << "Друкується: ";
				q.Dequeue().Print();
				cout << endl;
			}
		}
		else if (choice == 3)
		{
			q.Print();
		}
		cout << endl;
	}
}