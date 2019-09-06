#include <iostream>
#include <string>
#include <conio.h>
#include <Windows.h>
#include "BusList.h"
using namespace std;

int main()
{
	AutoPark park;
	int choice = -1;
	int busNumber, route;
	string driver;
	while (choice != 0)
	{
		system("cls");
		park.PrintPark();
		park.PrintRoute();
		cout << "\nMain menu:" << endl;
		cout << "(1) Buy bus   (2) Sell bus   (3) Send to route   (4) Send to park   (0) Exit" << endl;
		cout << "Your choice: ";
		cin >> choice;
		switch (choice)
		{
		case 1:
			cout << "Enter busnumber: ";
			cin >> busNumber;
			cout << "Enter route number: ";
			cin >> route;
			cout << "Enter driver\'s name and initials: ";
			cin >> driver;
			park.GetPark().addFirst({ busNumber, route, driver });
			break;
		case 2:
			if (!park.GetPark().isEmpty())
				park.GetPark().DeleteNode(park.Selection(park.GetPark(), "Sell bus (pick a bus and press Enter)"));
			else
				cout << "Nothing to sell. Park is empty." << endl;
			break;
		case 3:
			if (!park.GetPark().isEmpty())
				park.SendToRoute(park.Selection(park.GetPark(), "Send to route (pick a bus and press Enter)"));
			else
				cout << "No one to send to the route. Park is empty." << endl;
			break;
		case 4:
			if (!park.GetRoute().isEmpty())
				park.SendToPark(park.Selection(park.GetRoute(), "Send to park (pick a bus and press Enter)"));
			else
				cout << "No one to send to the park. Route is empty." << endl;
			break;
		case 0:
			cout << "Have a nice day." << endl;
			break;
		default:
			cout << "Invalid input. Try again." << endl;
			break;
		}
		system("pause");
	}
	return 0;
}