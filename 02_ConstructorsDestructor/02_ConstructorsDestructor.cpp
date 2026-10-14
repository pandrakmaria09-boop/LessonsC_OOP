#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

struct Coord
{
	int x;
	int y;
};

class Rectangle
{
	int width;
	int height;
	char symbol;
	Coord coord;
public:
	Rectangle()
	{
		width = 5;
		height = 3;
		symbol = '*';
		coord = { 0,0 };
	}
	Rectangle(int size)
	{
		if (size <= 0)
			size = 1;
		width = size;
		height = size;
		symbol = '*';
		coord = { 0,0 };
	}
	Rectangle(int width, int height)
	{
		if (width <= 0)
			width = 1;
		if (height <= 0)
			height = 1;
		this->width = width;
		this->height = height;
		symbol = '*';
		coord = { 0,0 };
	}
	void Print()
	{
		for (int i = 0; i < coord.y; i++)
			cout << endl;
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < coord.x; j++)
				cout << " ";
			for (int j = 0; j < width; j++)
				cout << symbol;
			cout << endl;
		}
	}
	void Resize(int h, int w)
	{
		if (height + h <= 0)
		{
			cout << " ---------- Wrong height! ----------" << endl;
			return;
		}
		if (width + w <= 0)
		{
			cout << " ---------- Wrong width! ----------" << endl;
			return;
		}
		height += h;
		width += w;
	}
	void Move(int x, int y)
	{
		if (coord.x + x < 0)
		{
			cout << " ---------- Wrong X! ----------" << endl;
			return;
		}
		if (coord.y + y < 0)
		{
			cout << " ---------- Wrong Y! ----------" << endl;
			return;
		}
		coord.x += x;
		coord.y += y;
	}
	void setSymbol(char symbol) { this->symbol = symbol; }
};
//2
class Student
{
	char* name;
	int age;
	int* marks;
	int countMarks;
	float averageMark;
	void SetAverageMark()
	{
		if (countMarks == 0)
		{
			averageMark = 0;
			return;
		}
		double summa = 0;
		for (int i = 0; i < countMarks; i++)
		{
			summa += marks[i];
		}
		averageMark = summa / countMarks;
	}
public:
	Student() : Student("no name", 1)//delegating constructor
	{
		cout << "Default constructor" << endl;
	}
	Student(const char* name, int age)
	{
		cout << "Parametrized constructor" << endl;
		this->name = new char[strlen(name) + 1];
		int i = 0;
		while (name[i] != '\0')
		{
			this->name[i] = name[i];
			i++;
		}
		this->name[i] = '\0';
		if (age <= 0)
			age = 1;
		this->age = age;
		marks = nullptr;
		countMarks = 0;
		averageMark = 0;
	}
	void AddMark(int mark)
	{
		if (mark < 1)
		{
			cout << "Wrong mark!" << endl;
			return;
		}
		if (mark > 12)
		{
			cout << "Wrong mark!" << endl;
			return;
		}
		int* temp = new int[countMarks + 1];
		for (int i = 0; i < countMarks; i++)
		{
			temp[i] = marks[i];
		}
		temp[countMarks] = mark;
		if (marks != nullptr)
			delete[]marks;
		marks = temp;
		countMarks++;
		SetAverageMark();
	}
	void Print()
	{
		cout << "Name : " << name << endl;
		cout << "Age : " << age << endl;
		cout << "Marks : ";
		for (int i = 0; i < countMarks; i++)
		{
			cout << marks[i] << " ";
		}
		cout << "\nCount marks : " << countMarks << endl;
		cout << "Average Mark : " << averageMark << endl;
	}
	void Save()
	{
		ofstream fout("student.txt");
		if (!fout.is_open())
		{
			cout << "Can't open file!" << endl;
			return;
		}
		fout << name << endl;
		fout << age << endl;
		fout << countMarks << endl;
		for (int i = 0; i < countMarks; i++)
		{
			fout << marks[i] << " ";
		}
		fout.close();
		cout << "Student saved" << endl;
	}
	void Load()
	{
		ifstream fin("student.txt");
		if (!fin.is_open())
		{
			cout << "File not found!" << endl;
			return;
		}
		char temp[100];
		fin.getline(temp, 100);
		setName(temp);
		fin >> age;
		if (marks != nullptr)
			delete[]marks;
		marks = nullptr;
		fin >> countMarks;
		if (countMarks > 0)
			marks = new int[countMarks];
		for (int i = 0; i < countMarks; i++)
		{
			fin >> marks[i];
		}
		SetAverageMark();
		fin.close();
		cout << "Student loaded" << endl;
	}
	const char* getName() { return name; }
	int getAge() { return age; }
	int getCountMarks() { return countMarks; }
	float getAverageMark() { return averageMark; }
	int getMark(int index)
	{
		if (index < 0)
		{
			cout << "Wrong index!" << endl;
			return 0;
		}
		if (index >= countMarks)
		{
			cout << "Wrong index!" << endl;
			return 0;
		}
		return marks[index];
	}
	void setName(const char* name)
	{
		delete[]this->name;
		this->name = new char[strlen(name) + 1];
		int i = 0;
		while (name[i] != '\0')
		{
			this->name[i] = name[i];
			i++;
		}
		this->name[i] = '\0';
	}
	void setAge(int age)
	{
		if (age <= 0)
		{
			cout << "Wrong age!" << endl;
			return;
		}
		this->age = age;
	}
	~Student()
	{
		cout << "Destructor " << name << endl;
		delete[]name;
		if (marks != nullptr)
			delete[]marks;
	}
};

int main()
{
	Rectangle r1;
	r1.Print();

	Rectangle r2(4);
	r2.setSymbol('#');
	r2.Print();

	Rectangle r3(8, 2);
	r3.setSymbol('+');
	r3.Move(3, 1);
	r3.Print();

	r3.Resize(1, -3);
	r3.Print();

	r3.Resize(-10, 0);
	r3.Move(-10, 0);

	//2
	Student student;
	student.Print();
	student.setName("Anton");
	student.setAge(17);
	student.AddMark(8);
	student.AddMark(10);
	student.AddMark(12);
	student.AddMark(15);
	student.Print();
	student.Save();

	Student st2("Vasia", 16);
	st2.AddMark(7);
	st2.AddMark(9);
	st2.Print();

	Student st3;
	st3.Load();
	st3.Print();
	cout << "Name : " << st3.getName() << ", Average : " << st3.getAverageMark() << endl;
}