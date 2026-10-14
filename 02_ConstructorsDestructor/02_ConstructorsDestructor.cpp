#include <iostream>
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
}