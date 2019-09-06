#pragma once
#include <iostream>
#include <iomanip>
#define ON true
#define OFF false

using namespace std;

void Highlight(bool state)
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (state)
		SetConsoleTextAttribute(hStdOut, 240);
	else
		SetConsoleTextAttribute(hStdOut, 15);
}

class Bus
{
private:
	int busNumber;
	string driver;
	int route;
protected:
	bool isValid(string driver)
	{
		return true; //dummy
	}
public:
	Bus() :busNumber(0), driver("-"), route(0) {}
	Bus(int busNumber, int route, string driver = "-") :Bus()
	{
		SetBusNumber(busNumber);
		SetDriver(driver);
		SetRoute(route);
	}
	void SetBusNumber(int busNumber)
	{
		if (busNumber > 0)
			this->busNumber = busNumber;
	}
	void SetDriver(string driver)
	{
		if (isValid(driver))
			this->driver = driver;
		else
			throw "Not valid driver";
	}
	void SetRoute(int route)
	{
		if (route > 0)
			this->route = route;
	}
	int GetBusNumber() const { return busNumber; }
	string GetDriver() const { return driver; }
	int GetRoute() const { return route; }
};

class BusList
{
protected:
	struct Node
	{
		Bus data;
		Node* prev, * next;
		Node(Bus data, Node* next = nullptr, Node* prev = nullptr) :data(data), next(next), prev(prev) {}
	};
private:
	Node* first, * last;
	size_t size;
public:
	BusList() { first = nullptr; last = nullptr; size = 0; }
	bool isEmpty() const { return first == nullptr; }
	void addFirst(Bus data)
	{
		Node* add = new Node(data, first);
		if (isEmpty())
			last = add;
		else
			first->prev = add;
		first = add;
		++size;
	}
	void addLast(Bus data)
	{
		Node* add = new Node(data, nullptr, last);
		if (isEmpty())
			first = add;
		else
			last->next = add;
		last = add;
		size++;
	}
	void DelFirst()
	{
		if (!isEmpty())
		{
			if (first == last)
			{
				delete first;
				first = last = nullptr;
			}
			else
			{
				Node* del = first;
				first = first->next;
				first->prev = nullptr;
				delete del;
			}
			size--;
		}
	}
	void DelLast()
	{
		if (!isEmpty())
		{
			if (first == last)
			{
				delete last;
				first = last = nullptr;
			}
			else
			{
				Node* del = last;
				last = last->prev;
				last->next = nullptr;
				delete del;
			}
			size--;
		}
	}
	void Clear()
	{
		while (!isEmpty())
			DelFirst();
	}
	int GetSize() const { return size; }
	Bus GetData(int number)
	{
		Node* get = first;
		for (int i = 1; i < number; i++)
			get = get->next;
		return get->data;
	}
	void DeleteNode(int number)
	{
		if (number > size || number < 1)
			return;
		Node* del = first;
		if (number == 1)
			DelFirst();
		else if (number == size)
			DelLast();
		else
		{
			for (int i = 1; i < number; i++)
				del = del->next;
			del->next->prev = del->prev;
			del->prev->next = del->next;
			delete del;
			size--;
		}
	}
	void Print(int highlightLine = 0) const
	{
		if (isEmpty())
			cout << "List is empty." << endl;
		else
		{
			Node* tmp = first;
			for (size_t i = 0; i < size; i++)
			{
				if (i + 1 == highlightLine)
					Highlight(ON);
				cout << "# " << setw(3) << i + 1 << ":  " << setw(15) << "Busnumber: " << setw(5) << tmp->data.GetBusNumber() << "  "
					 << setw(10) << "Route: " << setw(5) << tmp->data.GetRoute() << "  " << setw(10) << "Driver: " << tmp->data.GetDriver();
				cout << endl;
				Highlight(OFF);
				tmp = tmp->next;
			}
		}
	}
};

class AutoPark
{
private:
	BusList park;
	BusList route;
public:
	AutoPark()
	{
		park.addFirst({123, 33, "Petrov N.N."});
		park.addFirst({456, 44, "Ivanov I.I."});
		park.addFirst({789, 55, "Sidorov D.F."});
		park.addFirst({184, 22, "Pushkin A.S."});
		route.addFirst({553, 56, "Kernighan B.W."});
		route.addFirst({344, 32, "Ritchie D.M."});
		route.addFirst({453, 31, "Prata S."});
		route.addFirst({311, 67, "Stroustrup B."});
	}
	void SendToRoute(int number)
	{
		route.addFirst(park.GetData(number));
		park.DeleteNode(number);
	}
	void SendToPark(int number)
	{
		park.addFirst(route.GetData(number));
		route.DeleteNode(number);
	}
	void PrintPark()
	{
		cout << "Park:" << endl;
		park.Print();
	}
	void PrintRoute()
	{
		cout << "Route:" << endl;
		route.Print();
	}
	int Selection(const BusList& list, string message = "")
	{
		int code = -1, value = 0;
		while (code != 13) {
			system("cls");
			code = -1;
			value = (value + list.GetSize()) % list.GetSize();
			if (message.size() > 0)
				cout << message << endl;
			list.Print(value + 1);
			while (code != 72 && code != 80 && code != 13)
			{
				code = _getch();
				if (code == 72)
					value--;
				else if (code == 80)
					value++;
			}
		}
		return value + 1;
	}
	BusList& GetPark()
	{
		return park;
	}
	BusList& GetRoute()
	{
		return route;
	}
};