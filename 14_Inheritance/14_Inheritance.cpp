#include <iostream>
#include <string>
using namespace std;

//1

class Student {
protected:
	string name;
	string surname;
	string group;
	int age;
public:
	Student() :name("no name"), surname("no surname"), group("no group"), age(0) {}
	Student(string n, string s, string g, int a) :name(n), surname(s), group(g), age(a) {}
	void Print()const
	{
		cout << "Name : " << name << endl;
		cout << "Surname : " << surname << endl;
		cout << "Group : " << group << endl;
		cout << "Age : " << age << endl;
	}
};


class Aspirant : public Student
{
	string topic;          
	int pages;             
	bool defended;         // чи захищена дисертація
	static const int needPages = 100; 
public:
	Aspirant() :topic("no topic"), pages(0), defended(false), Student() {}
	Aspirant(string n, string s, string g, int a, string t) :topic(t), pages(0), defended(false), Student(n, s, g, a) {}

	void WriteDissertation(int p)
	{
		if (defended)
		{
			cout << "Dissertation is already defended!" << endl;
		}
		else
		{
			pages += p;
			cout << "Wrote " << p << " pages. Total pages : " << pages << endl;
		}
	}
	void Defend()
	{
		if (defended)
		{
			cout << "Dissertation is already defended!" << endl;
		}
		else
		{
			if (pages >= needPages)
			{
				defended = true;
				cout << "Dissertation is defended! Congratulations!" << endl;
			}
			else
			{
				cout << "Not enough pages to defend! Need " << needPages - pages << " more." << endl;
			}
		}
	}
	void Print()const
	{
		cout << "--------------------Aspirant----------------" << endl;
		Student::Print();
		cout << "Topic : " << topic << endl;
		cout << "Pages : " << pages << endl;
		if (defended)
			cout << "Defended : yes" << endl;
		else
			cout << "Defended : no" << endl;
	}
};

//2

class Passport {
protected:
	string name;
	string surname;
	string birthDate;
	string number;     
	string issuedBy;    // ким виданий
	string issueDate;   // коли 
public:
	Passport() :name("no name"), surname("no surname"), birthDate("00.00.0000"),
		number("no number"), issuedBy("no data"), issueDate("00.00.0000") {
	}
	Passport(string n, string s, string b, string num, string by, string d)
		:name(n), surname(s), birthDate(b), number(num), issuedBy(by), issueDate(d) {
	}
	void Print()const
	{
		cout << "Name : " << name << endl;
		cout << "Surname : " << surname << endl;
		cout << "Birth date : " << birthDate << endl;
		cout << "Passport number : " << number << endl;
		cout << "Issued by : " << issuedBy << endl;
		cout << "Issue date : " << issueDate << endl;
	}
};


class ForeignPassport : public Passport
{
	string foreignNumber;        
	string visas[10];            
	int visaCount;               // скільки віз зара
public:
	ForeignPassport() :foreignNumber("no number"), visaCount(0), Passport() {}
	ForeignPassport(string n, string s, string b, string num, string by, string d, string fnum)
		:foreignNumber(fnum), visaCount(0), Passport(n, s, b, num, by, d) {
	}

	void AddVisa(string visa)
	{
		if (visaCount < 10)
		{
			visas[visaCount] = visa;
			visaCount++;
			cout << "Visa added : " << visa << endl;
		}
		else
		{
			cout << "No place for new visas!" << endl;
		}
	}
	void Print()const
	{
		cout << "--------------------Foreign passport----------------" << endl;
		Passport::Print();
		cout << "Foreign passport number : " << foreignNumber << endl;
		cout << "Visas (" << visaCount << ") :" << endl;
		int i = 0;
		while (i < visaCount)
		{
			cout << "  " << i + 1 << ". " << visas[i] << endl;
			i++;
		}
	}
};



int main()
{
	Aspirant asp("Ivan", "Petrenko", "A-11", 24, "Inheritance in C++");
	asp.Print();

	asp.Defend();           
	asp.WriteDissertation(40);
	asp.WriteDissertation(35);
	asp.Defend();          
	asp.WriteDissertation(30);
	asp.Defend();           
	asp.Defend();           

	asp.Print();

	cout << endl;
	cout << endl;
	cout << endl;
	cout << endl;

	Passport p("Olena", "Shevchenko", "12.05.2005", "AA123456", "Rivne RVU", "20.05.2021");
	cout << "--------------------Passport----------------" << endl;
	p.Print();
	cout << endl;

	ForeignPassport fp("Olena", "Shevchenko", "12.05.2005", "AA123456", "Rivne RVU", "20.05.2021", "FE987654");
	fp.AddVisa("Poland, type C, till 01.09.2027");
	fp.AddVisa("Germany, type C, till 15.03.2028");
	fp.AddVisa("USA, type B, till 10.10.2030");
	cout << endl;
	fp.Print();
}