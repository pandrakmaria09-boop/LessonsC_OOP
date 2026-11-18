#include <iostream>
#define NOGDI
#include <windows.h>
using namespace std;

struct Point {
    int x, y;
};

void gotoxy(int x, int y)
{
    COORD c = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void DrawLine(Point a, Point b)
{
    int dx = b.x - a.x;
    int dy = b.y - a.y;
    int steps = abs(dx);
    if (abs(dy) > steps)
    {
        steps = abs(dy);
    }
    if (steps == 0)
    {
        gotoxy(a.x, a.y);
        cout << "*";
        return;
    }
    for (int i = 0; i <= steps; i++)
    {
        gotoxy(a.x + dx * i / steps, a.y + dy * i / steps);
        cout << "*";
    }
}

class Shape {
protected:
    string type;
public:
    Shape(string type) :type(type) {}
    virtual void Print()const = 0;
    virtual ~Shape() {}
};

class Line : public Shape
{
    Point start;
    Point end;
public:
    Line(Point start, Point end) :Shape("Лінія"), start(start), end(end) {}
    void Print()const override
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
        DrawLine(start, end);
    }
};

class Rectangle : public Shape
{
    Point topLeft;
    int width;
    int length;
public:
    Rectangle(Point topLeft, int width, int length) :
        Shape("Прямокутник"), topLeft(topLeft), width(width), length(length) {
    }
    void Print()const override
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
        for (int i = 0; i < width; i++)
        {
            gotoxy(topLeft.x + i, topLeft.y);
            cout << "*";
            gotoxy(topLeft.x + i, topLeft.y + length - 1);
            cout << "*";
        }
        for (int i = 0; i < length; i++)
        {
            gotoxy(topLeft.x, topLeft.y + i);
            cout << "*";
            gotoxy(topLeft.x + width - 1, topLeft.y + i);
            cout << "*";
        }
    }
};

class Polyline : public Shape
{
    Point* points;
    int countPoints;
public:
    Polyline(initializer_list<Point> list) :Shape("Ламана")
    {
        countPoints = list.size();
        points = new Point[countPoints];
        int i = 0;
        for (Point p : list)
        {
            points[i] = p;
            i++;
        }
    }
    void Print()const override
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
        for (int i = 0; i < countPoints - 1; i++)
        {
            DrawLine(points[i], points[i + 1]);
        }
    }
    ~Polyline()
    {
        if (points != nullptr)
            delete[]points;
    }
};

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    Shape* group[3]
    {
        new Line({ 2, 2 }, { 30, 8 }),
        new Rectangle({ 40, 2 }, 20, 7),
        new Polyline({ { 5, 12 }, { 15, 18 }, { 25, 12 }, { 35, 18 }, { 45, 12 } }),
    };

    for (int i = 0; i < 3; i++)
    {
        group[i]->Print();
        delete group[i];
    }

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    gotoxy(0, 22);
}