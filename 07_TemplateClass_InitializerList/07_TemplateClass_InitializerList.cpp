#include <iostream>
#include <string>
using namespace std;

template<typename T>
class Array
{
	T* arr;
	int size;
public:
	Array()
	{
		size = 0;
		arr = nullptr;
	}
	explicit Array(int size)
	{
		this->size = size;
		arr = new T[size]{};
	}
	Array(initializer_list<T> list)
	{
		this->size = list.size();
		this->arr = new T[size];
		int i = 0;
		for (T elem : list)
		{
			arr[i] = elem;
			i++;
		}
	}
	void Fill(initializer_list<T> list)
	{
		if (arr != nullptr)
			delete[]arr;
		this->size = list.size();
		this->arr = new T[size];
		int i = 0;
		for (T elem : list)
		{
			arr[i] = elem;
			i++;
		}
	}
	~Array()
	{
		if (arr != nullptr)
			delete[]arr;
	}

	void Print()
	{
		for (int i = 0; i < size; i++)
		{
			cout << arr[i] << " ";
		}
		cout << endl;
	}

	T GetMax();
	T GetMin();
	void Sort();
	int BinarySearch(T value);
	void Replace(int index, T value);
};

template<typename T>
T Array<T>::GetMax()
{
	T max = arr[0];
	for (int i = 0; i < size; i++)
	{
		if (arr[i] > max)
			max = arr[i];
	}
	return max;
}

template<typename T>
T Array<T>::GetMin()
{
	T min = arr[0];
	for (int i = 0; i < size; i++)
	{
		if (arr[i] < min)
			min = arr[i];
	}
	return min;
}

template<typename T>
void Array<T>::Sort()
{
	for (int i = 0; i < size - 1; i++)
	{
		for (int j = 0; j < size - i - 1; j++)
		{
			if (arr[j] > arr[j + 1])
			{
				T temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}
}

// масив має бути відсортов\аний
template<typename T>
int Array<T>::BinarySearch(T value)
{
	int left = 0;
	int right = size - 1;
	while (left <= right)
	{
		int mid = (left + right) / 2;
		if (arr[mid] == value)
			return mid;
		if (arr[mid] < value)
			left = mid + 1;
		else
			right = mid - 1;
	}
	return -1;
}

template<typename T>
void Array<T>::Replace(int index, T value)
{
	if (index >= 0 && index < size)
		arr[index] = value;
}

int main()
{
	Array<int> arr(5);
	arr.Print();

	Array<int> arr2({ 4, 7, 8, 9, 6, 5, 2, 6, 55, 44 });
	arr2.Print();
	cout << "Max : " << arr2.GetMax() << endl;
	cout << "Min : " << arr2.GetMin() << endl;

	arr2.Sort();
	arr2.Print();
	cout << "Index of 9 : " << arr2.BinarySearch(9) << endl;
	cout << "Index of 100 : " << arr2.BinarySearch(100) << endl;

	arr2.Replace(0, 1000);
	arr2.Print();

	arr2.Fill({ 3,2,1 });
	arr2.Print();

	Array<double> arr3 = { 3.3, 1.1, 2.2 };
	arr3.Sort();
	arr3.Print();

	Array<string> arr4{ "red", "green", "blue" };
	arr4.Sort();
	arr4.Print();
	cout << "Max : " << arr4.GetMax() << endl;
	arr4.Replace(1, "pink");
	arr4.Print();
}