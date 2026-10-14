//Конструктор викликається лише при створенні нового об'єкта.
//new новий масив ? скопіювати ? delete[] старий ? arr = новий ? size++
//При порожньому масиві arr дорівнює nullptr, а розіменування nullptr призводить до невизначеної поведінки, зазвичай до аварійного завершення програми.
//«правило трьох» - Деструктор, конструктор копіювання, оператор присвоєння
//Після delete[] вказівник зберігає стару адресу (висячий вказівник). Значення nullptr захищає від випадкового використання й подвійного видалення.
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

class Array
{
private:
	long* arr;
	int size;
public:
	// конструктор за замовчуванням
	Array()
	{
		this->arr = nullptr;
		this->size = 0;
	}
	// кконструктор з розміром (всі елементи = 0)
	Array(int size)
	{
		if (size < 0)
		{
			cout << "Error: negative size, array will be empty" << endl;
			size = 0;
		}
		this->size = size;
		if (size == 0)
		{
			this->arr = nullptr;
		}
		else
		{
			this->arr = new long[size];
			for (int i = 0; i < size; i++)
			{
				this->arr[i] = 0;
			}
		}
	}
	// Конструктор копіювання - створює новий об'єкт як точну, але незалежну копію іншого об'єкта.
	Array(const Array& other)
	{
		this->size = other.size;
		if (other.arr == nullptr)
		{
			this->arr = nullptr;
		}
		else
		{
			this->arr = new long[size];
			for (int i = 0; i < size; i++)
			{
				this->arr[i] = other.arr[i];
			}
		}
	}

	// pfgjdytyyz 
	void FillDefault()
	{
		if (size == 0)
		{
			cout << "Array is empty, nothing to fill" << endl;
			return;
		}
		for (int i = 0; i < size; i++)
		{
			arr[i] = i + 1;
		}
	}
	void FillRandom(int min = 0, int max = 100)
	{
		if (size == 0)
		{
			cout << "Array is empty, nothing to fill" << endl;
			return;
		}
		if (min > max)
		{
			int t = min;
			min = max;
			max = t;
		}
		for (int i = 0; i < size; i++)
		{
			arr[i] = min + rand() % (max - min + 1);
		}
	}
	void FillKeyboard()
	{
		if (size == 0)
		{
			cout << "Array is empty, nothing to fill" << endl;
			return;
		}
		for (int i = 0; i < size; i++)
		{
			cout << "arr[" << i << "] = ";
			cin >> arr[i];
		}
	}

	
	void Print()
	{
		cout << "Size : " << size << endl;
		cout << "Array : ";
		if (size == 0)
		{
			cout << "empty";
		}
		for (int i = 0; i < size; i++)
		{
			cout << arr[i] << " ";
		}
		cout << endl;
	}

	// додавання // видалення 
	void AddElement(long value)
	{
		long* temp = new long[size + 1];
		for (int i = 0; i < size; i++)
		{
			temp[i] = arr[i];
		}
		temp[size] = value;
		if (arr != nullptr)
			delete[]arr;
		arr = temp;
		size++;
	}
	bool DeleteByIndex(int index)
	{
		if (size == 0)
		{
			cout << "Error: array is empty" << endl;
			return false;
		}
		if (index < 0 || index >= size)
		{
			cout << "Error: index " << index << " is out of range" << endl;
			return false;
		}
		if (size == 1)
		{
			delete[]arr;
			arr = nullptr;
			size = 0;
			return true;
		}
		long* temp = new long[size - 1];
		for (int i = 0, j = 0; i < size; i++)
		{
			if (i != index)
			{
				temp[j] = arr[i];
				j++;
			}
		}
		delete[]arr;
		arr = temp;
		size--;
		return true;
	}
	bool DeleteByValue(long value)
	{
		if (size == 0)
		{
			cout << "Error: array is empty" << endl;
			return false;
		}
		for (int i = 0; i < size; i++)
		{
			if (arr[i] == value)
			{
				return DeleteByIndex(i);
			}
		}
		cout << "Error: value " << value << " not found" << endl;
		return false;
	}


	void Sort(bool ascending = true)
	{
		if (size < 2)
		{
			cout << "Nothing to sort" << endl;
			return;
		}
		for (int i = 0; i < size - 1; i++)
		{
			for (int j = 0; j < size - i - 1; j++)
			{
				bool needSwap = ascending ? (arr[j] > arr[j + 1]) : (arr[j] < arr[j + 1]);
				if (needSwap)
				{
					long t = arr[j];
					arr[j] = arr[j + 1];
					arr[j + 1] = t;
				}
			}
		}
	}

	
	long GetMin()
	{
		if (size == 0)
		{
			cout << "Error: array is empty" << endl;
			return 0;
		}
		long min = arr[0];
		for (int i = 1; i < size; i++)
		{
			if (arr[i] < min)
				min = arr[i];
		}
		return min;
	}
	long GetMax()
	{
		if (size == 0)
		{
			cout << "Error: array is empty" << endl;
			return 0;
		}
		long max = arr[0];
		for (int i = 1; i < size; i++)
		{
			if (arr[i] > max)
				max = arr[i];
		}
		return max;
	}
	double GetAverage()
	{
		if (size == 0)
		{
			cout << "Error: array is empty" << endl;
			return 0;
		}
		double sum = 0;
		for (int i = 0; i < size; i++)
		{
			sum += arr[i];
		}
		return sum / size;
	}

	// деструктор - автоматично викликається системою в момент знищення об'єкта 
	void Delete()
	{
		if (arr != nullptr)
			delete[]arr;
		arr = nullptr;
		size = 0;
	}
	~Array()
	{
		Delete();
	}
};

int main()
{
	srand(time(0));

	Array a;
	cout << "Default constructor:" << endl;
	a.Print();
	a.GetMin();
	a.DeleteByIndex(0);

	Array b(5);
	cout << "\nConstructor with size (zeros):" << endl;
	b.Print();

	b.FillRandom(-20, 50);
	cout << "\nRandom:" << endl;
	b.Print();

	b.AddElement(77);
	b.AddElement(-5);
	cout << "\nAfter adding 77 and -5:" << endl;
	b.Print();

	b.Sort(true);
	cout << "\nAscending:" << endl;
	b.Print();
	b.Sort(false);
	cout << "Descending:" << endl;
	b.Print();

	cout << "\nMin = " << b.GetMin() << endl;
	cout << "Max = " << b.GetMax() << endl;
	cout << "Average = " << b.GetAverage() << endl;

	cout << "\nDelete by index 1:" << endl;
	b.DeleteByIndex(1);
	b.Print();
	cout << "Delete by value 77:" << endl;
	b.DeleteByValue(77);
	b.Print();
	cout << "Delete not existing value 1000:" << endl;
	b.DeleteByValue(1000);
	cout << "Delete by wrong index 50:" << endl;
	b.DeleteByIndex(50);

	Array copy = Array(b);
	cout << "\nOriginal" << endl;
	b.Print();
	cout << "Copy" << endl;
	copy.Print();

	copy.AddElement(999);
	cout << "\nAfter changing copy (original must stay the same):" << endl;
	cout << "Original" << endl;
	b.Print();
	cout << "Copy" << endl;
	copy.Print();

	Array c(3);
	c.FillDefault();
	cout << "\nDefault values:" << endl;
	c.Print();

	
}