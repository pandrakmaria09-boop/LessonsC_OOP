#include <iostream>
#include <windows.h>
#include <string>
using namespace std;

class Book {
    string author;
    string title;
    string publ;
    int year;
    int pages;
public:
    explicit Book(string a, string t, string p, int y, int pg)
    {
        author = a;
        title = t;
        publ = p;
        year = y;
        pages = pg;
    }
    string getAuthor() const
    {
        return author;
    }
    string getPubl() const
    {
        return publ;
    }
    int getYear() const
    {
        return year;
    }
    void show() const
    {
        cout << author << " | " << title << " | " << publ << " | "
            << year << " | " << pages << " стор." << endl;
    }
};

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    const int n = 6;
    Book b[n] = {
        Book("Тарас Шевченко", "Кобзар", "А-БА-БА-ГА-ЛА-МА-ГА", 2019, 704),
        Book("Леся Українка", "Лісова пісня", "Фоліо", 2017, 160),
        Book("Тарас Шевченко", "Гайдамаки", "Фоліо", 2021, 224),
        Book("Іван Франко", "Захар Беркут", "Основи", 2015, 256),
        Book("Леся Українка", "Contra spem spero", "Основи", 2023, 128),
        Book("Іван Франко", "Мойсей", "А-БА-БА-ГА-ЛА-МА-ГА", 2020, 192)
    };

    string a;
    string p;
    int y;
    int i;

    cout << "Автор: ";
    getline(cin, a);
    cout << "Книги автора " << a << ":" << endl;
    i = 0;
    while (i < n)
    {
        if (b[i].getAuthor() == a)
        {
            b[i].show();
        }
        i++;
    }

    cout << "Видавництво: ";
    getline(cin, p);
    cout << "Книги видавництва " << p << ":" << endl;
    i = 0;
    while (i < n)
    {
        if (b[i].getPubl() == p)
        {
            b[i].show();
        }
        i++;
    }

    cout << "Рік: ";
    cin >> y;
    cout << "Книги після " << y << " року:" << endl;
    i = 0;
    while (i < n)
    {
        if (b[i].getYear() > y)
        {
            b[i].show();
        }
        i++;
    }

 
}