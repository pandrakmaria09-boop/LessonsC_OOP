#include <iostream>
#include <windows.h>
#include <string>
#include <vector>
using namespace std;

class Abonent
{
private:
    string pib;      
    string dom;      
    string rob;      
    string mob;     
    string info;    
    static int kilkist;  

public:
    Abonent(string p, string d, string r, string m, string i)
    {
        pib = p;
        dom = d;
        rob = r;
        mob = m;
        info = i;
        kilkist++;
    }

    //делегування 
    Abonent() : Abonent("", "", "", "", "") {}
    Abonent(string p) : Abonent(p, "", "", "", "") {}
    Abonent(string p, string m) : Abonent(p, "", "", m, "") {}
    Abonent(const Abonent& a) : Abonent(a.pib, a.dom, a.rob, a.mob, a.info) {}

    ~Abonent()
    {
        kilkist--;
    }

    
    string getPib() { return pib; }
    string getDom() { return dom; }
    string getRob() { return rob; }
    string getMob() { return mob; }
    string getInfo() { return info; }

    void setPib(string p) { pib = p; }
    void setDom(string d) { dom = d; }
    void setRob(string r) { rob = r; }
    void setMob(string m) { mob = m; }
    void setInfo(string i) { info = i; }

    void show()
    {
        cout << "ПІБ: " << pib << endl;
        cout << "Домашній тел: " << dom << endl;
        cout << "Робочий тел: " << rob << endl;
        cout << "Мобільний тел : " << mob << endl;
        cout << "Інфо: " << info << endl;
        cout << "------------------------" << endl;
    }

    static int getKilkist() { return kilkist; }
};

int Abonent::kilkist = 0;

int main()
{
    SetConsoleCP(1251);         
    SetConsoleOutputCP(1251);
    vector<Abonent> kniga;
    int vybir = -1;

    while (vybir != 0)
    {
        cout << endl;
        cout << "1 - додати абонента" << endl;
        cout << "2 - показати всіх" << endl;
        cout << "3 - знайти за ПІБ" << endl;
        cout << "4 - видалити за N" << endl;
        cout << "5 - к-сть абонентів" << endl;
        cout << "0 - exit" << endl;
        cout << "інший вибір: ";
        cin >> vybir;
        cin.ignore();

        if (vybir == 1)
        {
            string p, d, r, m, i;
            cout << "ПІБ: ";
            getline(cin, p);
            cout << "домашній тел: ";
            getline(cin, d);
            cout << "Робочий тел: ";
            getline(cin, r);
            cout << "мобільний тел: ";
            getline(cin, m);
            cout << "додаткова інфа: ";
            getline(cin, i);
            kniga.push_back(Abonent(p, d, r, m, i));
            cout << "--------------- фбонента додано!---------------" << endl;
        }
        else if (vybir == 2)
        {
            if (kniga.size() == 0)
            {
                cout << "порожньо" << endl;
            }
            int k = 0;
            while (k < kniga.size())
            {
                cout << "№" << k + 1 << endl;
                kniga[k].show();
                k++;
            }
        }
        else if (vybir == 3)
        {
            string p;
            bool znaid = false;
            cout << "введіть піб: ";
            getline(cin, p);
            int k = 0;
            while (k < kniga.size())
            {
                if (kniga[k].getPib() == p)
                {
                    kniga[k].show();
                    znaid = true;
                }
                k++;
            }
            if (znaid == false)
            {
                cout << "---------------------не знайдено------------------" << endl;
            }
        }
        else if (vybir == 4)
        {
            int n;
            cout << "номер абонента: ";
            cin >> n;
            if (n >= 1 && n <= kniga.size())
            {
                kniga.erase(kniga.begin() + n - 1);
                cout << "видаляємо" << endl;
            }
            else
            {
                cout << "не правильний номер" << endl;
            }
        }
        else if (vybir == 5)
        {
            cout << "абонентів: " << Abonent::getKilkist() << endl;
        }
    }

 
}