#include <iostream>
using namespace std;

class EmptyListException : public exception
{
public:
	EmptyListException(const char* message) :exception(message) {}
};

class InvalidPositionException : public exception
{
	int pos;
public:
	InvalidPositionException(const char* message, int pos) :pos(pos),
		exception(message) {
	}
	void Message()
	{
		cout << what() << endl;
		cout << "Position : " << pos << endl;
	}
};

class List
{
private:
	struct Node
	{
		int data;
		Node* next;
		Node* prev;
		Node(int data) :data(data), next(nullptr), prev(nullptr) {}
	};
	Node* head;
	Node* tail;
	int size;

	Node* CreateNode(int value)
	{
		try
		{
			return new Node(value);
		}
		catch (bad_alloc)
		{
			throw exception("Can't allocate memory");
		}
	}
	Node* GetNode(int pos)
	{
		Node* cur;
		if (pos < size / 2)
		{
			cur = head;
			for (int i = 0; i < pos; i++)
			{
				cur = cur->next;
			}
		}
		else
		{
			cur = tail;
			for (int i = size - 1; i > pos; i--)
			{
				cur = cur->prev;
			}
		}
		return cur;
	}
public:
	List() :head(nullptr), tail(nullptr), size(0) {}
	~List()
	{
		while (head != nullptr)
		{
			Node* temp = head;
			head = head->next;
			delete temp;
		}
	}
	int GetSize()const
	{
		return size;
	}
	bool IsEmpty()const
	{
		return size == 0;
	}
	void AddToHead(int value)
	{
		Node* node = CreateNode(value);
		if (head == nullptr)
		{
			head = tail = node;
		}
		else
		{
			node->next = head;
			head->prev = node;
			head = node;
		}
		size++;
	}
	void AddToTail(int value)
	{
		Node* node = CreateNode(value);
		if (tail == nullptr)
		{
			head = tail = node;
		}
		else
		{
			node->prev = tail;
			tail->next = node;
			tail = node;
		}
		size++;
	}
	void InsertByPos(int pos, int value)
	{
		if (pos < 0 || pos > size)
			throw InvalidPositionException("Invalid position", pos);
		if (pos == 0)
		{
			AddToHead(value);
			return;
		}
		if (pos == size)
		{
			AddToTail(value);
			return;
		}
		Node* node = CreateNode(value);
		Node* cur = GetNode(pos);
		node->prev = cur->prev;
		node->next = cur;
		cur->prev->next = node;
		cur->prev = node;
		size++;
	}
	void RemoveFromHead()
	{
		if (IsEmpty())
			throw EmptyListException("List is empty");
		Node* temp = head;
		head = head->next;
		if (head == nullptr)
			tail = nullptr;
		else
			head->prev = nullptr;
		delete temp;
		size--;
	}
	void RemoveFromTail()
	{
		if (IsEmpty())
			throw EmptyListException("List is empty");
		Node* temp = tail;
		tail = tail->prev;
		if (tail == nullptr)
			head = nullptr;
		else
			tail->next = nullptr;
		delete temp;
		size--;
	}
	void RemoveByPos(int pos)
	{
		if (IsEmpty())
			throw EmptyListException("List is empty");
		if (pos < 0 || pos >= size)
			throw InvalidPositionException("Invalid position", pos);
		if (pos == 0)
		{
			RemoveFromHead();
			return;
		}
		if (pos == size - 1)
		{
			RemoveFromTail();
			return;
		}
		Node* cur = GetNode(pos);
		cur->prev->next = cur->next;
		cur->next->prev = cur->prev;
		delete cur;
		size--;
	}

	int GetElementByPos(int pos)
	{
		if (IsEmpty())
			throw EmptyListException("List is empty");
		if (pos < 0 || pos >= size)
			throw InvalidPositionException("Invalid position", pos);
		return GetNode(pos)->data;
	}
	void SetElementByPos(int pos, int value)
	{
		if (IsEmpty())
			throw EmptyListException("List is empty");
		if (pos < 0 || pos >= size)
			throw InvalidPositionException("Invalid position", pos);
		GetNode(pos)->data = value;
	}
	void Print()const
	{
		if (IsEmpty())
			throw EmptyListException("List is empty");
		Node* cur = head;
		while (cur != nullptr)
		{
			cout << cur->data << " ";
			cur = cur->next;
		}
		cout << endl;
	}
};

int main()
{
	List list;

	try
	{
		list.Print();
	}
	catch (EmptyListException ex)
	{
		cout << "Empty : " << ex.what() << endl;
	}

	try
	{
		list.RemoveFromHead();
	}
	catch (EmptyListException ex)
	{
		cout << "Empty : " << ex.what() << endl;
	}

	try
	{
		list.AddToTail(10);
		list.AddToTail(20);
		list.AddToHead(5);
		list.InsertByPos(1, 7);
		list.Print();

		cout << list.GetElementByPos(2) << endl;
		list.SetElementByPos(3, 25);
		list.RemoveByPos(0);
		list.Print();

		list.InsertByPos(100, 1);
	}
	catch (InvalidPositionException ex)
	{
		ex.Message();
	}
	catch (EmptyListException ex)
	{
		cout << "Empty : " << ex.what() << endl;
	}
	catch (exception ex)
	{
		cout << "General error : " << ex.what() << endl;
	}
	catch (...)
	{
		cout << "Unknown exception" << endl;
	}

	try
	{
		cout << list.GetElementByPos(-1) << endl;
	}
	catch (InvalidPositionException ex)
	{
		ex.Message();
	}

	try
	{
		list.RemoveByPos(10);
	}
	catch (InvalidPositionException ex)
	{
		ex.Message();
	}
	catch (EmptyListException ex)
	{
		cout << "Empty : " << ex.what() << endl;
	}
}