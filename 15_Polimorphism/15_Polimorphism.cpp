#include <iostream>
using namespace std;

class Shape
{
private:
	string name;
protected:
	string type;
public:
	Shape() :name("no name"), type("no type") {}
	Shape(string n, string t) :name(n), type(t) {}
	virtual float GetArea()const
	{
		return 0;
	}
	virtual void Show()const
	{
		cout << "---------------Shape------------------" << endl;
		cout << "Name : " << name << endl;
		cout << "Type : " << type << endl;
	}
	virtual void Draw()const {}
};
class Rectangle : public Shape
{
	float a;
	float b;
public:
	Rectangle() : a(0), b(0), Shape() {}
	Rectangle(string n, float a, float b) : a(a), b(b),
		Shape(n, "Rectangle") {
	}
	float GetArea()const override
	{
		return a * b;
	}
	void Show()const override
	{
		Shape::Show();
		cout << "Side A : " << a << endl;
		cout << "Side B : " << b << endl;
	}
	void Draw()const override
	{
		for (int i = 0; i < (int)b; i++)
		{
			for (int j = 0; j < (int)a; j++)
				cout << "* ";
			cout << endl;
		}
		cout << endl;
	}
};
class Circle : public Shape
{
	float r;
public:
	Circle() : r(0), Shape() {}
	Circle(string n, float r) : r(r),
		Shape(n, "Circle") {
	}
	float GetArea()const override
	{
		return 3.14f * r * r;
	}
	void Show()const override
	{
		Shape::Show();
		cout << "Radius : " << r << endl;
	}
	void Draw()const override
	{
		int radius = (int)r;
		int diameter = radius * 2;
		for (int i = 0; i <= diameter; i++)
		{
			for (int j = 0; j <= diameter; j++)
			{
				int x = i - radius;
				int y = j - radius;
				if (x * x + y * y <= radius * radius)
					cout << "* ";
				else
					cout << "  ";
			}
			cout << endl;
		}
		cout << endl;
	}
};
class RightTriangle : public Shape
{
	float a;
	float b;
public:
	RightTriangle() : a(0), b(0), Shape() {}
	RightTriangle(string n, float a, float b) : a(a), b(b),
		Shape(n, "Right Triangle") {
	}
	float GetArea()const override
	{
		return a * b / 2;
	}
	void Show()const override
	{
		Shape::Show();
		cout << "Leg A : " << a << endl;
		cout << "Leg B : " << b << endl;
	}
	void Draw()const override
	{
		int w = (int)a;
		int h = (int)b;
		for (int i = 0; i < h; i++)
		{
			int stars = (i + 1) * w / h;
			if (stars < 1)
				stars = 1;
			for (int j = 0; j < stars; j++)
				cout << "* ";
			cout << endl;
		}
		cout << endl;
	}
};
class Triangle : public Shape
{
	float a;
	float h;
public:
	Triangle() : a(0), h(0), Shape() {}
	Triangle(string n, float a, float h) : a(a), h(h),
		Shape(n, "Triangle") {
	}
	float GetArea()const override
	{
		return a * h / 2;
	}
	void Show()const override
	{
		Shape::Show();
		cout << "Base : " << a << endl;
		cout << "Height : " << h << endl;
	}
	void Draw()const override
	{
		int w = (int)a;
		int height = (int)h;
		for (int i = 0; i < height; i++)
		{
			int stars = (i + 1) * w / height;
			if (stars < 1)
				stars = 1;
			int spaces = (w - stars) / 2;
			for (int j = 0; j < spaces; j++)
				cout << "  ";
			for (int j = 0; j < stars; j++)
				cout << "* ";
			cout << endl;
		}
		cout << endl;
	}
};
class Trapezoid : public Shape
{
	float a;
	float b;
	float h;
public:
	Trapezoid() : a(0), b(0), h(0), Shape() {}
	Trapezoid(string n, float a, float b, float h) : a(a), b(b), h(h),
		Shape(n, "Trapezoid") {
	}
	float GetArea()const override
	{
		return (a + b) / 2 * h;
	}
	void Show()const override
	{
		Shape::Show();
		cout << "Base A : " << a << endl;
		cout << "Base B : " << b << endl;
		cout << "Height : " << h << endl;
	}
	void Draw()const override
	{
		int top = (int)a;
		int bottom = (int)b;
		int height = (int)h;
		int maxWidth = top > bottom ? top : bottom;
		for (int i = 0; i < height; i++)
		{
			int stars = top + (bottom - top) * i / (height > 1 ? height - 1 : 1);
			int spaces = (maxWidth - stars) / 2;
			for (int j = 0; j < spaces; j++)
				cout << "  ";
			for (int j = 0; j < stars; j++)
				cout << "* ";
			cout << endl;
		}
		cout << endl;
	}
};
void TestShape(Shape& shape)
{
	shape.Show();
	cout << "Area : " << shape.GetArea() << endl;
	cout << endl;
	shape.Draw();
}
int main()
{
	Rectangle rect("Rect1", 5, 10);
	Circle circle("Circle1", 4);
	RightTriangle rtri("RTriangle1", 3, 4);
	Triangle tri("Triangle1", 6, 5);
	Trapezoid trap("Trapezoid1", 4, 8, 5);

	TestShape(rect);
	TestShape(circle);
	TestShape(rtri);
	TestShape(tri);
	TestShape(trap);

	Shape* shapes[5]{
		new Rectangle("Rect2", 2, 7),
		new Circle("Circle2", 2),
		new RightTriangle("RTriangle2", 6, 8),
		new Triangle("Triangle2", 10, 3),
		new Trapezoid("Trapezoid2", 3, 5, 4)
	};

	for (int i = 0; i < 5; i++)
	{
		shapes[i]->Show();
		cout << "Area : " << shapes[i]->GetArea() << endl;
		cout << endl;
		shapes[i]->Draw();
		delete shapes[i];
	}
}