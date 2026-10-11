#include <iostream>
#include <string>
#include <fstream>
#include <windows.h>
using namespace std;

//1
class Student
{
private:
    string name;          
    string birthDate;     
    string phone;         
    string city;          
    string country;       
    string schoolName;   
    string schoolCity;   
    string schoolCountry; 
    string group;         
public:
    // введення
    void Init()
    {

        HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(h, 11);
        cout << "Enter name : "; getline(cin, name);
        cout << "Enter birth date : "; getline(cin, birthDate);
        cout << "Enter phone : "; getline(cin, phone);
        cout << "Enter city : "; getline(cin, city);
        cout << "Enter country : "; getline(cin, country);
        cout << "Enter school name : "; getline(cin, schoolName);
        cout << "Enter school city : "; getline(cin, schoolCity);
        cout << "Enter school country : "; getline(cin, schoolCountry);
        cout << "Enter group : "; getline(cin, group);
    }

    // виведення 
    void Print()
    {
        cout << "Name : " << name << endl;
        cout << "Birth date : " << birthDate << endl;
        cout << "Phone : " << phone << endl;
        cout << "City : " << city << endl;
        cout << "Country : " << country << endl;
        cout << "School name : " << schoolName << endl;
        cout << "School city : " << schoolCity << endl;
        cout << "School country : " << schoolCountry << endl;
        cout << "Group : " << group << endl;
    }

    // setters --  (кладе значення в змінну)
    //setter	записує	нічого не повертає (void)
    void setName(string name)
    {
        this->name = name;
    }
    void setBirthDate(string birthDate)
    {
        this->birthDate = birthDate;
    }
    void setPhone(string phone)
    {
        this->phone = phone;
    }
    void setCity(string city)
    {
        this->city = city;
    }
    void setCountry(string country)
    {
        this->country = country;
    }
    void setSchoolName(string schoolName)
    {
        this->schoolName = schoolName;
    }
    void setSchoolCity(string schoolCity)
    {
        this->schoolCity = schoolCity;
    }
    void setSchoolCountry(string schoolCountry)
    {
        this->schoolCountry = schoolCountry;
    }
    void setGroup(string group)
    {
        this->group = group;
    }

    // getters -- метод (який віддає значення зі змінної)
    // getter	читає	return змінна
    string getName()
    {
        return name;
    }
    string getBirthDate()
    {
        return birthDate;
    }
    string getPhone()
    {
        return phone;
    }
    string getCity()
    {
        return city;
    }
    string getCountry()
    {
        return country;
    }
    string getSchoolName()
    {
        return schoolName;
    }
    string getSchoolCity()
    {
        return schoolCity;
    }
    string getSchoolCountry()
    {
        return schoolCountry;
    }
    string getGroup()
    {
        return group;
    }
};

//2
class Point
{
private:
    int x;
    int y;
    int z;
public:
    // введення 
    void Init()
    {
        cout << "Enter x : "; cin >> x;
        cout << "Enter y : "; cin >> y;
        cout << "Enter z : "; cin >> z;
    }

    // вивед
    void Print()
    {
        cout << "Point : (" << x << ", " << y << ", " << z << ")" << endl;
    }

    // setters
    void setX(int x)
    {
        this->x = x;
    }
    void setY(int y)
    {
        this->y = y;
    }
    void setZ(int z)
    {
        this->z = z;
    }

    // getters
    int getX()
    {
        return x;
    }
    int getY()
    {
        return y;
    }
    int getZ()
    {
        return z;
    }

    // зберігаємо в файл
    void SaveToFile(string fileName)
    {
        ofstream fout(fileName);
        if (fout.is_open())
        {
            fout << x << " " << y << " " << z << endl;
            fout.close();
            cout << "Saved to file " << fileName << endl;
        }
        else
        {
            cout << "Error: can not open file " << fileName << endl;
        }
    }

    // завантаження з файлу
    void LoadFromFile(string fileName)
    {
        ifstream fin(fileName);
        if (fin.is_open())
        {
            fin >> x;
            fin >> y;
            fin >> z;
            fin.close();
            cout << "Loaded from file " << fileName << endl;
        }
        else
        {
            cout << "Error: can not open file " << fileName << endl;
        }
    }
};

int main()
{
    // 1
    cout << "===== Student =====" << endl;
    Student st;
    st.Init();
    cout << endl;
    st.Print();

    // робота з аксесорами --  спочатку через сеттери змінюємо значення, а потім через геттери перевіряємо, що воно змінилося
    st.setGroup("PV-21");
    st.setCity("Rivne");
    cout << endl;
    cout << "Name : " << st.getName() << endl;
    cout << "City : " << st.getCity() << endl;
    cout << "Group : " << st.getGroup() << endl;

    //2
    cout << endl << "===== Point =====" << endl;
    Point p;
    p.Init();
    p.Print();

    //аксесори
    p.setX(100);
    p.setY(200);
    p.setZ(300);
    cout << "x = " << p.getX() << " y = " << p.getY() << " z = " << p.getZ() << endl;

    // file
    p.SaveToFile("point.txt");

    Point p2;
    p2.LoadFromFile("point.txt");
    p2.Print();

   
}