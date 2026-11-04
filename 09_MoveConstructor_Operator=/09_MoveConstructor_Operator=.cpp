#include <iostream>
#include <windows.h>
using namespace std;


void gotoxy(int x, int y)
{
	COORD c;
	c.X = (SHORT)x;
	c.Y = (SHORT)y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

// 1 Point
class Point
{
	int x;
	int y;

public:
	Point() : x(0), y(0) {}
	Point(int x, int y) : x(x), y(y) {}
	Point(const Point& p) : x(p.x), y(p.y) {}

	int GetX() const { return x; }
	int GetY() const { return y; }

	void Print() const
	{
		cout << "(" << x << ":" << y << ")" << endl;
	}

	// ++p
	Point& operator++()
	{
		x++;
		y++;
		return *this;
	}
	// p++
	Point operator++(int)
	{
		Point old(*this);
		x++;
		y++;
		return old;
	}
	// --p
	Point& operator--()
	{
		x--;
		y--;
		return *this;
	}
	// p--
	Point operator--(int)
	{
		Point old(*this);
		x--;
		y--;
		return old;
	}

	// > : ц€ точка дал≥ в≥д (0:0), н≥ж p
	bool operator>(const Point& p) const
	{
		int d1 = x * x + y * y;
		int d2 = p.x * p.x + p.y * p.y;
		if (d1 > d2)
		{
			return true;
		}
		return false;
	}
	bool operator<(const Point& p) const
	{
		int d1 = x * x + y * y;
		int d2 = p.x * p.x + p.y * p.y;
		if (d1 < d2)
		{
			return true;
		}
		return false;
	}

	Point& operator!()
	{
		x = -x;
		y = -y;
		return *this;
	}
};


class Vector
{
	Point* points;
	int countPoint;

public:
	Vector() : points(nullptr), countPoint(0) {}

	Vector(const Vector& v)
	{
		cout << "Copy constructor" << endl;
		countPoint = v.countPoint;
		if (countPoint > 0)
		{
			points = new Point[countPoint];
			int i = 0;
			while (i < countPoint)
			{
				points[i] = v.points[i];
				i++;
			}
		}
		else
		{
			points = nullptr;
		}
	}

	Vector(Vector&& v) noexcept
	{
		cout << "Move constructor" << endl;
		points = v.points;
		countPoint = v.countPoint;
		v.points = nullptr;
		v.countPoint = 0;
	}

	Vector& operator=(const Vector& v)
	{
		cout << "Copy operator =" << endl;
		if (this == &v)
		{
			return *this;
		}
		delete[] points;
		countPoint = v.countPoint;
		if (countPoint > 0)
		{
			points = new Point[countPoint];
			int i = 0;
			while (i < countPoint)
			{
				points[i] = v.points[i];
				i++;
			}
		}
		else
		{
			points = nullptr;
		}
		return *this;
	}


	Vector& operator=(Vector&& v) noexcept
	{
		cout << "Move operator =" << endl;
		if (this == &v)
		{
			return *this;
		}
		delete[] points;
		points = v.points;
		countPoint = v.countPoint;
		v.points = nullptr;
		v.countPoint = 0;
		return *this;
	}

	
	~Vector()
	{
		delete[] points;
	}


	void Add(const Point& p)
	{
		Point* t = new Point[countPoint + 1];
		int i = 0;
		while (i < countPoint)
		{
			t[i] = points[i];
			i++;
		}
		t[countPoint] = p;
		delete[] points;
		points = t;
		countPoint++;
	}

	
	void Print() const
	{
		cout << "Points: " << countPoint << endl;
		int i = 0;
		while (i < countPoint)
		{
			cout << i + 1 << ") ";
			points[i].Print();
			i++;
		}
	}

	// * додаткове 
	// виводить точки в потр≥бних координатах консольк≥
	void Show() const
	{
		int i = 0;
		while (i < countPoint)
		{
			int x = points[i].GetX();
			int y = points[i].GetY();
			if (x >= 0)
			{
				if (y >= 0)
				{
					gotoxy(x, y);
					cout << "*";
				}
			}
			i++;
		}
	}
};

Vector TestVector()
{
	Vector t;
	t.Add(Point(10, 5));
	t.Add(Point(20, 8));
	return t;
}

int main()
{
	
	Point a(3, 4);
	Point b(1, 2);
	a.Print();
	b.Print();

	++a;
	cout << "++a: ";
	a.Print();
	--a;
	cout << "--a: ";
	a.Print();

	if (a > b)
	{
		cout << "a дал≥ в≥д (0:0), н≥ж b" << endl;
	}
	if (b < a)
	{
		cout << "b ближче до (0:0), н≥ж a" << endl;
	}

	!a;
	cout << "!a: ";
	a.Print();
	cout << endl;

	

	Vector v;
	v.Add(Point(5, 3));
	v.Add(Point(15, 6));
	v.Add(Point(25, 10));
	v.Print();

	Vector c(v);               // коп
	Vector m(TestVector());    // перем≥щенн€
	Vector e;
	e = v;                     // оператор = (коп≥юванн€)
	e = TestVector();          // оператор = (перем≥щенн€)
	m.Print();

	system("cls");
	v.Show();
	gotoxy(0, 15);
	system("pause");
	
}