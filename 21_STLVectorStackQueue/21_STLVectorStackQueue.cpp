#include <iostream>
#include <fstream>
#include <vector>
#include <windows.h>
#include <string>
#include <algorithm>
using namespace std;

struct Time
{
    short h, m, s;
};

class Train
{
private:
    int number;
    Time departureTime;
    string destination;

public:
    Train() : number(0), destination("")
    {
        departureTime.h = 0;
        departureTime.m = 0;
        departureTime.s = 0;
    }

    int getNumber() const { return number; }
    Time getTime() const { return departureTime; }
    string getDestination() const { return destination; }

    void setTime(Time t) { departureTime = t; }

    bool operator<(const Train& other) const
    {
        if (departureTime.h != other.departureTime.h)
            return departureTime.h < other.departureTime.h;
        if (departureTime.m != other.departureTime.m)
            return departureTime.m < other.departureTime.m;
        return departureTime.s < other.departureTime.s;
    }

 
    friend ostream& operator<<(ostream& out, const Train& t)
    {
        out << t.number << " "
            << t.departureTime.h << " "
            << t.departureTime.m << " "
            << t.departureTime.s << " "
            << t.destination;
        return out;
    }



    friend istream& operator>>(istream& in, Train& t)
    {
        in >> t.number
            >> t.departureTime.h
            >> t.departureTime.m
            >> t.departureTime.s;
        in >> ws;
        getline(in, t.destination);
        return in;
    }
};

class Railway
{
    vector<Train> trains;

public:
    // 1
    void addTrain()
    {
        Train t;
        cout << "¬вед≥ть: номер години хвилини секунди станц≥ю\n";
        cin >> t;
        trains.push_back(t);
        cout << "ѕот€г додано\n";
    }

    // 2
    void showAll()
    {
        if (trains.size() == 0)
        {
            cout << "—писок порожн≥й\n";
            return;
        }
        for (int i = 0; i < trains.size(); i++)
        {
            cout << trains[i] << endl;
        }
    }

    // 3
    void showByNumber()
    {
        int number;
        cout << "¬вед≥ть номер пот€га: ";
        cin >> number;
        bool found = false;
        for (int i = 0; i < trains.size(); i++)
        {
            if (trains[i].getNumber() == number)
            {
                cout << trains[i] << endl;
                found = true;
            }
        }
        if (found == false)
        {
            cout << "ѕот€г не знайдено\n";
        }
    }

    // 4
    void editTime()
    {
        int number;
        cout << "¬вед≥ть номер пот€га: ";
        cin >> number;
        bool found = false;
        for (int i = 0; i < trains.size(); i++)
        {
            if (trains[i].getNumber() == number)
            {
                Time t;
                cout << "¬вед≥ть новий час (години хвилини секунди): ";
                cin >> t.h >> t.m >> t.s;
                trains[i].setTime(t);
                found = true;
                cout << "„ас зм≥нено\n";
            }
        }
        if (found == false)
        {
            cout << "ѕот€г не знайдено\n";
        }
    }

    // 5
    void sortByTime()
    {
        sort(trains.begin(), trains.end());
        cout << "—писок в≥дсортовано\n";
    }

    // 6
    void showByDestination()
    {
        string dest;
        cout << "¬вед≥ть станц≥ю призначенн€: ";
        cin >> ws;
        getline(cin, dest);
        bool found = false;
        for (int i = 0; i < trains.size(); i++)
        {
            if (trains[i].getDestination() == dest)
            {
                cout << trains[i] << endl;
                found = true;
            }
        }
        if (found == false)
        {
            cout << "ѕот€г≥в до ц≥Їњ станц≥њ немаЇ\n";
        }
    }


    void saveToFile()
    {
        ofstream f("trains.txt");
        f << trains.size() << endl;
        for (int i = 0; i < trains.size(); i++)
        {
            f << trains[i] << endl;
        }
        f.close();
    }


    void loadFromFile()
    {
        ifstream f("trains.txt");
        if (!f.is_open())
        {
            return;
        }
        int n;
        f >> n;
        trains.clear();
        for (int i = 0; i < n; i++)
        {
            Train t;
            f >> t;
            trains.push_back(t);
        }
        f.close();
    }
};

int main()
{

    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);


    Railway r;
    r.loadFromFile();

    int choice = -1;
    while (choice != 0)
    {
        cout << "\n===== «ал≥зничний вокзал =====\n";
        cout << "1. додати пот€г\n";
        cout << "2. показати вс≥ пот€ги\n";
        cout << "3. показати пот€г по номеру\n";
        cout << "4. редагувати час в≥дправки\n";
        cout << "5. сортувати по часу в≥дправленн€\n";
        cout << "6. пот€ги по станц≥њ призначенн€\n";
        cout << "0. ¬их≥д\n";
        cout << "¬аш вар≥ант: ";
        cin >> choice;

        if (choice == 1)
        {
            r.addTrain();
        }
        else if (choice == 2)
        {
            r.showAll();
        }
        else if (choice == 3)
        {
            r.showByNumber();
        }
        else if (choice == 4)
        {
            r.editTime();
        }
        else if (choice == 5)
        {
            r.sortByTime();
        }
        else if (choice == 6)
        {
            r.showByDestination();
        }
    }

    r.saveToFile();
    
}