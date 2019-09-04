#include <iostream>
#include "DList.h"
using namespace std;

int main()
{
	CDlist<int> list;
	CDlist<int> list2;
	list2.addFirst(1);
	list2.addFirst(55);
	list2.addFirst(3);
	list2.addFirst(4);
	list2.addFirst(5);
	list2.Print();
	list.addFirst(5);
	list.addLast(5);
	list.addLast(5);
	list.addLast(5);
	list.addLast(5);
	list.InsertBefore(11, 2);
	list.InsertAfter(13, 2);
	list.addLast(7);
	list.addLast(55);
	list.Print();
	cout << "=======================" << endl;
	cout << "Replaces: " << list.Replace(5, 99) << endl;
	cout << "=======================" << endl;
	list.Print();
	cout << "rotate" << endl;
	list.Rotate();
	list.Print();
	CDlist<int> sumlist = list + list2;
	sumlist.Print();
	cout << "*****************" << endl;
	CDlist<int> multlist = list * list2;
	multlist.Print();
	system("pause");
	return 0;
}