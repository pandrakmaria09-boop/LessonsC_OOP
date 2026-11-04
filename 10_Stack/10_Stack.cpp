#include <iostream>
#include <initializer_list>
using namespace std;

template <typename T>
class Stack
{
private:
	enum { EMPTY = -1 };
	T* arr;
	int size;
	int topIndex;

public:
	Stack() : arr(nullptr), size(0), topIndex(EMPTY) {}

	Stack(int size) : size(size)
	{
		arr = new T[size];
		topIndex = EMPTY;
	}

	Stack(int size, initializer_list<T> list) : size(size)
	{
		if (list.size() > size)
		{
			this->size = list.size();
		}
		arr = new T[this->size];
		topIndex = EMPTY;
		for (T elem : list)
		{
			arr[++topIndex] = elem;
		}
	}

	Stack(const Stack& other) = delete;

	~Stack()
	{
		if (arr != nullptr)
		{
			delete[] arr;
		}
	}

	bool IsFull()
	{
		return topIndex == size - 1;
	}

	bool IsEmpty()
	{
		return topIndex == EMPTY;
	}

	void Resize()
	{
		int newSize = size * 2;
		if (newSize == 0)
		{
			newSize = 1;
		}
		T* temp = new T[newSize];
		int i = 0;
		while (i <= topIndex)
		{
			temp[i] = arr[i];
			i++;
		}
		delete[] arr;
		arr = temp;
		size = newSize;
	}

	bool Push(T elem)
	{
		if (IsFull())
		{
			Resize();
		}
		arr[++topIndex] = elem;
		return true;
	}

	T Pop()
	{
		if (!IsEmpty())
		{
			return arr[topIndex--];
		}
		return T();
	}

	int GetCount()
	{
		return topIndex + 1;
	}

	void Clear()
	{
		topIndex = EMPTY;
	}

	T Peek()
	{
		if (!IsEmpty())
		{
			return arr[topIndex];
		}
		return T();
	}

	void Print()
	{
		for (int i = 0; i <= topIndex; i++)
		{
			cout << arr[i] << " ";
		}
		cout << endl;
	}
};

int main()
{
	Stack<char> st(3, { 'a', 'b', 'c' });
	cout << "Size = " << st.GetCount() << endl;
	st.Print();

	st.Push('d');
	st.Push('e');
	cout << "Size = " << st.GetCount() << endl;
	st.Print();

	cout << "Top = " << st.Peek() << endl;

	while (!st.IsEmpty())
	{
		cout << "Delete element : " << st.Pop() << endl;
		st.Print();
	}
	cout << "Size = " << st.GetCount() << endl;

	Stack<int> s(2);
	s.Push(10);
	s.Push(20);
	s.Push(30);
	s.Print();
	s.Clear();
	cout << "Size = " << s.GetCount() << endl;
}