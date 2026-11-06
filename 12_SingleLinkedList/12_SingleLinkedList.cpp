#include <iostream>
using namespace std;

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
	bool IsEmpty() const
	{
		return head == nullptr;
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
			cout << current->value << " ";
			current = current->next;
		}
		cout << endl;
	}
	~List()
	{
		Clear();
	}
};

class Point
{
	double x;
	double y;
public:
	Point(double x = 0, double y = 0) :x(x), y(y) {}
	friend ostream& operator<<(ostream& out, const Point& p)
	{
		out << "(" << p.x << ", " << p.y << ")";
		return out;
	}
};

class Vector
{
	int size;
	List<Point> points;
public:
	Vector() :size(0) {}

	Vector(const Point& p) :size(0)
	{
		AddToTail(p);
	}

	Vector(const Point* arr, int count) :size(0)
	{
		for (int i = 0; i < count; i++)
		{
			AddToTail(arr[i]);
		}
	}

	Vector(const Vector& other) :size(other.size), points(other.points) {}

	Vector& operator=(const Vector& other)
	{
		if (this != &other)
		{
			points = other.points;
			size = other.size;
		}
		return *this;
	}

	void AddToHead(const Point& p)
	{
		points.AddToHead(p);
		size++;
	}
	void AddToTail(const Point& p)
	{
		points.AddToTail(p);
		size++;
	}
	void DeleteFromHead()
	{
		if (size == 0) return;
		points.DeleteFromHead();
		size--;
	}
	void DeleteFromTail()
	{
		if (size == 0) return;
		points.DeleteFromTail();
		size--;
	}
	int GetSize() const
	{
		return size;
	}
	void Print() const
	{
		if (size == 0)
		{
			cout << "Vector is empty" << endl;
			return;
		}
		cout << "Vector (" << size << " points): ";
		points.Print();
	}
};

int main()
{
	List<int> l;
	l.AddToTail(100);
	l.AddToTail(200);
	l.AddToTail(300);
	l.AddToHead(50);
	l.Print();
	l.DeleteFromHead();
	l.Print();
	l.DeleteFromTail();
	l.Print();

	Vector v;
	v.AddToTail(Point(1, 2));
	v.AddToTail(Point(3, 4));
	v.AddToHead(Point(0, 0));
	v.Print();

	v.DeleteFromHead();
	v.Print();
	v.DeleteFromTail();
	v.Print();

	Point arr[] = { Point(5, 5), Point(6, 6), Point(7, 7) };
	Vector v2(arr, 3);
	Vector v3 = v2;
	v2.DeleteFromHead();
	v2.Print();
	v3.Print();

	Vector empty;
	empty.DeleteFromHead();
	empty.Print();
}