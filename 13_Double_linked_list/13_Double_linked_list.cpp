#define NOMINMAX
#include <iostream>
#include <string>
#include <iomanip>
#ifdef _WIN32
#include <windows.h>
#endif
using namespace std;

const string H = "\xE2\x94\x80";
const string V = "\xE2\x94\x82";
const string TL = "\xE2\x94\x8C";
const string TR = "\xE2\x94\x90";
const string BL = "\xE2\x94\x94";
const string BR = "\xE2\x94\x98";
const string TJ = "\xE2\x94\xAC";
const string BJ = "\xE2\x94\xB4";
const string LJ = "\xE2\x94\x9C";
const string RJ = "\xE2\x94\xA4";
const string X = "\xE2\x94\xBC";

const int W1 = 8, W2 = 7, W3 = 12, W4 = 6;

string Repeat(const string& s, int n)
{
	string result;
	for (int i = 0; i < n; i++)
	{
		result += s;
	}
	return result;
}

string Line(const string& left, const string& mid, const string& right)
{
	return left + Repeat(H, W1) + mid + Repeat(H, W2) + mid
		+ Repeat(H, W3) + mid + Repeat(H, W4) + right;
}

void Title(const string& text)
{
	int pad = 60 - (int)text.size() - 2;
	if (pad < 3) pad = 3;
	cout << endl << Repeat(H, 3) << " " << text << " " << Repeat(H, pad) << endl << endl;
}

template<typename T>
class List
{
	struct Node
	{
		T value;
		Node* next;
		Node() :value(), next(nullptr) {}
		Node(T value, Node* next) :value(value), next(next) {}
	};
	Node* head;
public:
	List()
	{
		head = nullptr;
	}
	List(const List& other) :head(nullptr)
	{
		Node* tail = nullptr;
		Node* current = other.head;
		while (current != nullptr)
		{
			Node* newNode = new Node(current->value, nullptr);
			if (head == nullptr) head = newNode;
			else tail->next = newNode;
			tail = newNode;
			current = current->next;
		}
	}
	List& operator=(const List& other)
	{
		if (this != &other)
		{
			Clear();
			Node* tail = nullptr;
			Node* current = other.head;
			while (current != nullptr)
			{
				Node* newNode = new Node(current->value, nullptr);
				if (head == nullptr) head = newNode;
				else tail->next = newNode;
				tail = newNode;
				current = current->next;
			}
		}
		return *this;
	}
	void AddToHead(T value)
	{
		Node* newNode = new Node(value, head);
		head = newNode;
	}
	void AddToTail(T value)
	{
		Node* newNode = new Node(value, nullptr);
		if (head == nullptr)
		{
			head = newNode;
		}
		else
		{
			Node* current = head;
			while (current->next != nullptr)
			{
				current = current->next;
			}
			current->next = newNode;
		}
	}
	void DeleteFromHead()
	{
		if (head == nullptr) return;
		Node* temp = head;
		head = head->next;
		delete temp;
	}
	void DeleteFromTail()
	{
		if (head == nullptr) return;
		if (head->next == nullptr)
		{
			delete head;
			head = nullptr;
		}
		else
		{
			Node* current = head;
			while (current->next->next != nullptr)
			{
				current = current->next;
			}
			delete current->next;
			current->next = nullptr;
		}
	}
	void Clear()
	{
		while (head != nullptr)
		{
			Node* current = head;
			head = head->next;
			delete current;
		}
	}
	void Print() const
	{
		Node* current = head;
		while (current != nullptr)
		{
			cout << current->value << endl;
			current = current->next;
		}
	}
	~List()
	{
		Clear();
	}
};

struct Vagon
{
	int number;
	int seats;
	int passengers;
	Vagon(int number = 0, int seats = 0, int passengers = 0)
		:number(number), seats(seats), passengers(passengers) {
	}

	friend ostream& operator<<(ostream& out, const Vagon& v)
	{
		int load = v.seats > 0 ? v.passengers * 100 / v.seats : 0;
		out << Line(LJ, X, RJ) << "\n"
			<< V << " " << setw(6) << v.number << " "
			<< V << " " << setw(5) << v.seats << " "
			<< V << " " << setw(10) << v.passengers << " "
			<< V << " " << setw(3) << load << "%" << " " << V;
		return out;
	}
};

class Train
{
	string model;
	int vagonCount;
	List<Vagon> vagons;
public:
	Train() :model("unknown"), vagonCount(0) {}

	Train(const string& model) :model(model), vagonCount(0) {}

	Train(const Train& other)
		:model(other.model), vagonCount(other.vagonCount), vagons(other.vagons) {
	}

	void AddToHead(const Vagon& v)
	{
		vagons.AddToHead(v);
		vagonCount++;
	}
	void AddToTail(const Vagon& v)
	{
		vagons.AddToTail(v);
		vagonCount++;
	}
	void DeleteFromHead()
	{
		if (vagonCount == 0) return;
		vagons.DeleteFromHead();
		vagonCount--;
	}
	void DeleteFromTail()
	{
		if (vagonCount == 0) return;
		vagons.DeleteFromTail();
		vagonCount--;
	}
	void Show() const
	{
		cout << "Train: " << model << "    Vagons: " << vagonCount << endl << endl;
		if (vagonCount == 0)
		{
			cout << "(no vagons)" << endl << endl;
			return;
		}
		cout << Line(TL, TJ, TR) << endl;
		cout << V << " Number " << V << " Seats " << V << " Passengers " << V << " Load " << V << endl;
		vagons.Print();
		cout << Line(BL, BJ, BR) << endl << endl;
	}
};

template<typename T>
class DoubleList
{
	struct Node
	{
		T value;
		Node* prev;
		Node* next;
		Node(T value, Node* prev, Node* next) :value(value), prev(prev), next(next) {}
	};
	Node* head;
	Node* tail;
public:
	DoubleList() :head(nullptr), tail(nullptr) {}
	DoubleList(const DoubleList& other) :head(nullptr), tail(nullptr)
	{
		for (Node* c = other.head; c != nullptr; c = c->next)
		{
			AddToTail(c->value);
		}
	}
	DoubleList& operator=(const DoubleList& other)
	{
		if (this != &other)
		{
			Clear();
			for (Node* c = other.head; c != nullptr; c = c->next)
			{
				AddToTail(c->value);
			}
		}
		return *this;
	}
	void AddToHead(T value)
	{
		Node* newNode = new Node(value, nullptr, head);
		if (head != nullptr) head->prev = newNode;
		else tail = newNode;
		head = newNode;
	}
	void AddToTail(T value)
	{
		Node* newNode = new Node(value, tail, nullptr);
		if (tail != nullptr) tail->next = newNode;
		else head = newNode;
		tail = newNode;
	}
	void DeleteFromHead()
	{
		if (head == nullptr) return;
		Node* temp = head;
		head = head->next;
		if (head != nullptr) head->prev = nullptr;
		else tail = nullptr;
		delete temp;
	}
	void DeleteFromTail()
	{
		if (tail == nullptr) return;
		Node* temp = tail;
		tail = tail->prev;
		if (tail != nullptr) tail->next = nullptr;
		else head = nullptr;
		delete temp;
	}
	void Clear()
	{
		while (head != nullptr)
		{
			DeleteFromHead();
		}
	}
	void Print() const
	{
		for (Node* c = head; c != nullptr; c = c->next)
		{
			cout << c->value << " ";
		}
		cout << endl;
	}
	~DoubleList()
	{
		Clear();
	}
};

int main()
{
#ifdef _WIN32
	SetConsoleOutputCP(CP_UTF8);
#endif

	Title("Train: added 3 vagons");
	Train t("Intercity");
	t.AddToTail(Vagon(1, 36, 20));
	t.AddToTail(Vagon(2, 54, 50));
	t.AddToHead(Vagon(0, 20, 10));
	t.Show();

	Title("Train: deleted from head");
	t.DeleteFromHead();
	t.Show();

	Title("Train: deleted from tail");
	t.DeleteFromTail();
	t.Show();

	Title("Copy: t2 = t, then t.DeleteFromHead()");
	Train t2 = t;
	t.DeleteFromHead();
	cout << "[t]" << endl;
	t.Show();
	cout << "[t2 - copy]" << endl;
	t2.Show();

	Title("Empty train");
	Train empty;
	empty.DeleteFromHead();
	empty.Show();

	Title("DoubleList<int>");
	DoubleList<int> d;
	d.AddToTail(10);
	d.AddToTail(20);
	d.AddToTail(30);
	d.AddToHead(5);
	cout << "after adding:      ";
	d.Print();
	cout << endl;
	d.DeleteFromHead();
	cout << "delete from head:  ";
	d.Print();
	cout << endl;
	d.DeleteFromTail();
	cout << "delete from tail:  ";
	d.Print();
	cout << endl;
	d.DeleteFromHead();
	d.DeleteFromHead();
	d.DeleteFromHead();
	cout << "list is empty:     ";
	d.Print();
	cout << endl;
}