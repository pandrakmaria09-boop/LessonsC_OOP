#include <iostream>
#include <iomanip>
#include <string>
#include <windows.h>
using namespace std;

HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

// 1
class Employer
{
protected:
    string name;
    int age;
public:
    Employer() :name("без імені"), age(0) {}
    Employer(string n, int a) :name(n), age(a) {}
    virtual void Print() = 0;
};

class President : public Employer
{
    string country;
public:
    President() :country("без країни"), Employer() {}
    President(string n, int a, string c) :country(c), Employer(n, a) {}
    void Print() override
    {
        SetConsoleTextAttribute(h, 14);
        cout << "| " << left << setw(12) << "президент" << " | " << setw(10) << name
            << " | " << setw(5) << age << " | " << setw(20) << "країна: " + country << " |" << endl;
        SetConsoleTextAttribute(h, 7);
    }
};

class Manager : public Employer
{
    string department;
public:
    Manager() :department("без відділу"), Employer() {}
    Manager(string n, int a, string d) :department(d), Employer(n, a) {}
    void Print() override
    {
        SetConsoleTextAttribute(h, 11);
        cout << "| " << left << setw(12) << "менеджер" << " | " << setw(10) << name
            << " | " << setw(5) << age << " | " << setw(20) << "відділ: " + department << " |" << endl;
        SetConsoleTextAttribute(h, 7);
    }
};

class Worker : public Employer
{
    string job;
public:
    Worker() :job("без роботи"), Employer() {}
    Worker(string n, int a, string j) :job(j), Employer(n, a) {}
    void Print() override
    {
        SetConsoleTextAttribute(h, 10);
        cout << "| " << left << setw(12) << "працівник" << " | " << setw(10) << name
            << " | " << setw(5) << age << " | " << setw(20) << "робота: " + job << " |" << endl;
        SetConsoleTextAttribute(h, 7);
    }
};

// 2
class Transport
{
protected:
    string name;
    float speed;
public:
    Transport() :name("без назви"), speed(1) {}
    Transport(string n, float s) :name(n), speed(s) {}
    float Time(float dist)
    {
        return dist / speed;
    }
    virtual float Cost(float dist, int people, float cargo) = 0;
    virtual int Color() = 0;
    void Show(float dist, int people, float cargo)
    {
        SetConsoleTextAttribute(h, Color());
        cout << "| " << left << setw(12) << name << " | " << fixed << setprecision(2)
            << setw(10) << Time(dist) << " | " << setw(14) << Cost(dist, people, cargo) << " |" << endl;
        SetConsoleTextAttribute(h, 7);
    }
};

class Car : public Transport
{
public:
    Car() :Transport() {}
    Car(string n, float s) :Transport(n, s) {}
    float Cost(float dist, int people, float cargo) override
    {
        return dist * 10 + people * dist * 0.5 + cargo * dist * 0.05;
    }
    int Color() override
    {
        return 12;
    }
};

class Bicycle : public Transport
{
public:
    Bicycle() :Transport() {}
    Bicycle(string n, float s) :Transport(n, s) {}
    float Cost(float dist, int people, float cargo) override
    {
        return dist * 1 + people * dist * 0.2 + cargo * dist * 0.1;
    }
    int Color() override
    {
        return 9;
    }
};

class Cart : public Transport
{
public:
    Cart() :Transport() {}
    Cart(string n, float s) :Transport(n, s) {}
    float Cost(float dist, int people, float cargo) override
    {
        return dist * 3 + people * dist * 0.1 + cargo * dist * 0.02;
    }
    int Color() override
    {
        return 13;
    }
};

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    // 1
    President p("Іван", 55, "Україна");
    Manager m("Олена", 40, "продажі");
    Worker w("Петро", 28, "слюсар");
    Employer* e[3] = { &p, &m, &w };

    SetConsoleTextAttribute(h, 15);
    cout << "           служб0вці" << endl;
    SetConsoleTextAttribute(h, 7);
    cout << "+--------------+------------+-------+----------------------+" << endl;
    SetConsoleTextAttribute(h, 15);
    cout << "| " << left << setw(12) << "посада" << " | " << setw(10) << "ім'я"
        << " | " << setw(5) << "вік" << " | " << setw(20) << "інформація" << " |" << endl;
    SetConsoleTextAttribute(h, 7);
    cout << "+--------------+------------+-------+----------------------+" << endl;
    int i = 0;
    while (i < 3)
    {
        e[i]->Print();
        i++;
    }
    cout << "+--------------+------------+-------+----------------------+" << endl;

    cout << endl;

    // 2
    Car a("автомобіль", 80);
    Bicycle b("велосипед", 15);
    Cart c("віз", 5);
    Transport* t[3] = { &a, &b, &c };
    float dist = 100;
    int people = 2;
    float cargo = 50;

    SetConsoleTextAttribute(h, 15);
    cout << "     перевезення: 100 км, 2 пасажири, 50 кг вантажу" << endl;
    SetConsoleTextAttribute(h, 7);
    cout << "+--------------+------------+----------------+" << endl;
    SetConsoleTextAttribute(h, 15);
    cout << "| " << left << setw(12) << "транспорт" << " | " << setw(10) << "час (год)"
        << " | " << setw(14) << "вартість (грн)" << " |" << endl;
    SetConsoleTextAttribute(h, 7);
    cout << "+--------------+------------+----------------+" << endl;
    i = 0;
    while (i < 3)
    {
        t[i]->Show(dist, people, cargo);
        i++;
    }
    cout << "+--------------+------------+----------------+" << endl;
}