#include <iostream>
#include <string>
using namespace std;

//композиція

class Engine
{
	float volume;
	int power;
	string type;
public:
	Engine() :volume(0), power(0), type("none") {}
	Engine(float v, int p, string t) :volume(v), power(p), type(t) {}
	void ShowInfo()const
	{
		cout << "Engine : " << volume << " L, " << power << " h.p., " << type << endl;
	}
};

class Body
{
	string type;
	string color;
public:
	Body() :type("none"), color("no color") {}
	Body(string t, string c) :type(t), color(c) {}
	void ShowInfo()const
	{
		cout << "Body : " << type << ", color " << color << endl;
	}
};

class Wheel
{
	int radius;
	string brand;
public:
	Wheel() :radius(0), brand("none") {}
	Wheel(int r, string b) :radius(r), brand(b) {}
	void ShowInfo()const
	{
		cout << "Wheel : R" << radius << ", " << brand << endl;
	}
};

class Door
{
	string position;
	bool isOpen;
public:
	Door() :position("none"), isOpen(false) {}
	Door(string p) :position(p), isOpen(false) {}
	void ShowInfo()const
	{
		cout << "Door : " << position << ", ";
		if (isOpen == true)
		{
			cout << "open" << endl;
		}
		else
		{
			cout << "closed" << endl;
		}
	}
};

class Gearbox
{
	string type;
	int gears;
public:
	Gearbox() :type("none"), gears(0) {}
	Gearbox(string t, int g) :type(t), gears(g) {}
	void ShowInfo()const
	{
		cout << "Gearbox : " << type << ", " << gears << " gears" << endl;
	}
};

class Headlight
{
	string type;
	bool isOn;
public:
	Headlight() :type("none"), isOn(false) {}
	Headlight(string t) :type(t), isOn(false) {}
	void ShowInfo()const
	{
		cout << "Headlight : " << type << ", ";
		if (isOn == true)
		{
			cout << "on" << endl;
		}
		else
		{
			cout << "off" << endl;
		}
	}
};

//агрегація

class Driver
{
	string name;
	string surname;
	int age;
	int experience;
public:
	Driver() :name("none"), surname("none"), age(0), experience(0) {}
	Driver(string n, string s, int a, int e) :name(n), surname(s), age(a), experience(e) {}
	void ShowInfo()const
	{
		cout << "--------------- Driver : " << name << " " << surname << endl;
		cout << "Age : " << age << endl;
		cout << "Driving experience : " << experience << " years" << endl;
	}
};



class Car
{
	string brand;
	string model;
	int year;
	// композиція
	Engine engine;
	Body body;
	Wheel* wheels;
	int countWheels;
	Door* doors;
	int countDoors;
	Gearbox gearbox;
	Headlight headlights[2];
	// агрегація
	Driver* driver;
public:
	Car() :brand("none"), model("none"), year(0), wheels(nullptr), countWheels(0),
		doors(nullptr), countDoors(0), driver(nullptr) {
	}

	Car(string b, string m, int y) :brand(b), model(m), year(y), driver(nullptr),
		engine(2.0, 150, "Petrol"), body("Sedan", "Black"), gearbox("Automatic", 6)
	{
		countWheels = 4;
		wheels = new Wheel[countWheels];
		for (int i = 0; i < countWheels; i++)
		{
			wheels[i] = Wheel(17, "Michelin");
		}
		countDoors = 4;
		doors = new Door[countDoors];
		doors[0] = Door("Front left");
		doors[1] = Door("Front right");
		doors[2] = Door("Rear left");
		doors[3] = Door("Rear right");
		headlights[0] = Headlight("LED");
		headlights[1] = Headlight("LED");
	}

	

	Car(string b, string m, int y, Driver* d) :Car(b, m, y)
	{
		driver = d;
	}

	~Car()
	{
		if (wheels != nullptr)delete[]wheels;
		if (doors != nullptr)delete[]doors;
	}

	void AddDriver(Driver* driver)
	{
		this->driver = driver;
	}

	void Show()const
	{
		cout << "=============== Car : " << brand << " " << model << " (" << year << ")" << endl;
		engine.ShowInfo();
		body.ShowInfo();
		for (int i = 0; i < countWheels; i++)
		{
			wheels[i].ShowInfo();
		}
		for (int i = 0; i < countDoors; i++)
		{
			doors[i].ShowInfo();
		}
		gearbox.ShowInfo();
		for (int i = 0; i < 2; i++)
		{
			headlights[i].ShowInfo();
		}
		if (driver != nullptr)
		{
			driver->ShowInfo();
		}
		else
		{
			cout << "No driver" << endl;
		}
	}
};

int main()
{
	Driver driver1("Ivan", "Petrenko", 30, 8);

	
	Car car1("Toyota", "Camry", 2020, &driver1);
	car1.Show();

	cout << endl;

	

	Car car2("BMW", "X5", 2022);
	car2.Show();
	car2.AddDriver(&driver1);
	car2.Show();
}