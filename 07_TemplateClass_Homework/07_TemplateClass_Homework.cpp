#include <iostream>
#include <string>
#include <windows.h>
using namespace std;

class Airplane
{
	string model;
	string type;
	int count;     // к-сть пасажирів
	int maxCount;  
public:
	Airplane()
	{
		model = "No model";
		type = "No type";
		count = 0;
		maxCount = 0;
	}
	Airplane(string model, string type, int count, int maxCount)
	{
		this->model = model;
		this->type = type;
		this->maxCount = maxCount;
		if (count > maxCount)
		{
			cout << "Забагато пасажирів! Встановлено максимум." << endl;
			this->count = maxCount;
		}
		else
		{
			if (count < 0)
				this->count = 0;
			else
				this->count = count;
		}
	}

	void Print() const
	{
		cout << "Модель: " << model << endl;
		cout << "Тип: " << type << endl;
		cout << "Пасажирів: " << count << " / " << maxCount << endl;
		cout << "---------------------" << endl;
	}

	// ++ (префіксна форма) - додає одного пасажира
	Airplane& operator++()
	{
		if (count < maxCount)
			count++;
		else
			cout << "Салон повний, додати пасажира неможливо!" << endl;
		return *this;
	}

	// -- (префіксна форма) - забирає одного пасажира
	Airplane& operator--()
	{
		if (count > 0)
			count--;
		else
			cout << "Салон порожній, зменшити неможливо" << endl;
		return *this;
	}

	// () - збільшує к-сть пас на задане значення
	void operator()(int value)
	{
		if (value < 0)
		{
			cout << "Значення не може бути від'ємним" << endl;
			return;
		}
		if (count + value > maxCount)
			cout << "Перевищено макс. к-сть пасажирів!" << endl;
		else
			count += value;
	}


	friend bool operator==(const Airplane& left, const Airplane& right);
	friend bool operator>(const Airplane& left, const Airplane& right);
};

// == порівнює типи літаків
bool operator==(const Airplane& left, const Airplane& right)
{
	return left.type == right.type;
}

// > порівнює літаки за макс к-стю пас
bool operator>(const Airplane& left, const Airplane& right)
{
	return left.maxCount > right.maxCount;
}

int main()
{
	system("chcp 1251");

	Airplane a1("Boeing 737", "Passenger", 100, 150);
	Airplane a2("Airbus A320", "Passenger", 120, 180);
	Airplane a3("Antonov An-225", "Cargo", 0, 10);

	a1.Print();
	a2.Print();
	a3.Print();

	

	if (a1 == a2)
		cout << "a1 і a2 одного типу" << endl;
	else
		cout << "a1 і a2 різних типів" << endl;

	if (a1 == a3)
		cout << "a1 і a3 одного типу" << endl;
	else
		cout << "a1 і a3 різних типів" << endl;




	if (a1 > a2)
		cout << "У a1 більше місць, ніж у a2" << endl;
	else
		cout << "У a1 місць не більше, ніж у a2" << endl;

	if (a2 > a1)
		cout << "У a2 більше місць, ніж у a1" << endl;
	else
		cout << "У a2 місць не більше, ніж у a1" << endl;

	cout << endl;

	// ++ і --
	++a1;
	a1.Print();
	--a1;
	--a1;
	a1.Print();

	// ()
	a1(15);
	a1.Print();

	// перевірка  макс.
	a1(100);
	a1.Print();

	// перевірка ++ при повном салоні
	a3(10);
	++a3;
	a3.Print();

	// перевірка -- при порожньом
	Airplane a4("Test", "Test", 0, 5);
	--a4;



}