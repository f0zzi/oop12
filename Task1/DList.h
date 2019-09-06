#pragma once
#include <iostream>
using namespace std;

template<typename T>
class CDlist
{
protected:
	struct Node
	{
		T data;
		Node* prev, * next;
		Node(T data, Node* next = nullptr, Node* prev = nullptr) :data(data), next(next), prev(prev) {}
	};
private:
	Node* first, * last;
	size_t size;
public:
	CDlist() { first = nullptr; last = nullptr; size = 0; }
	Node* searchNode(T data)
	{
		Node* tmp = first;
		while (tmp != nullptr && tmp->data != data)
			tmp = tmp->next;
		return tmp;
	}
	bool isEmpty() const { return first == nullptr; }
	void addFirst(T data)
	{
		Node* add = new Node(data, first);
		if (isEmpty())
			last = add;
		else
			first->prev = add;
		first = add;
		++size;
	}
	void addLast(T data)
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
	void DeleteNode(T data)
	{
		Node* del = searchNode(data);
		if (del == nullptr)
			return;
		if (del == first)
			DelFirst();
		if (del == last)
			DelLast();
		else
		{
			del->next->prev = del->prev;
			del->prev->next = del->next;
			delete del;
			size--;
		}
	}
	void Print() const
	{
		if (isEmpty())
			cout << "List is empty." << endl;
		else
		{
			Node* tmp = first;
			for (size_t i = 0; i < size; i++)
			{
				cout << "Node# " << i + 1 << ":\t";
				cout << tmp->data << endl;
				tmp = tmp->next;
			}
		}
	}
	void PrintRev() const
	{
		if (isEmpty())
			cout << "List is empty." << endl;
		else
		{
			Node* tmp = last;
			for (int i = size - 1; i >= 0; i--)
			{
				cout << "Node# " << i + 1 << ":\t";
				cout << tmp->data << endl;
				tmp = tmp->prev;
			}
		}
	}
	void InsertBefore(T data, size_t place)
	{
		if (place > size)
			return;
		if (place == 1)
			addFirst(data);
		else
		{
			Node* tmp = first;
			for (size_t i = 1; i < place; i++)
			{
				tmp = tmp->next;
			}
			Node* add = new Node(data, tmp, tmp->prev);
			tmp->prev->next = add;
			tmp->prev = add;
			size++;
		}
	}
	void InsertAfter(T data, size_t place)
	{
		if (place > size)
			return;
		if (place == size)
			addLast(data);
		else
		{
			Node* tmp = first;
			for (size_t i = 1; i <= place; i++)
			{
				tmp = tmp->next;
			}
			Node* add = new Node(data, tmp, tmp->prev);
			tmp->prev->next = add;
			tmp->prev = add;
			size++;
		}
	}
	int Replace(T data, T newData)
	{
		int count = 0;
		Node* tmp = first;
		while (tmp != nullptr)
		{
			if (tmp->data == data)
			{
				tmp->data = newData;
				count++;
			}
			tmp = tmp->next;
		}
		return count;
	}
	void Rotate()
	{
		if (size > 1)
		{
			Node* next, * current = first;
			while (current != nullptr)
			{
				next = current->next;
				current->next = current->prev;
				current->prev = next;
				current = next;
			}
			current = first;
			first = last;
			last = current;
		}
	}
	CDlist operator+ (const CDlist& second)
	{
		CDlist<T> tmp;
		Node* tmpNode = first;
		while (tmpNode != nullptr)
		{
			tmp.addFirst(tmpNode->data);
			tmpNode = tmpNode->next;
		}
		tmpNode = second.first;
		while (tmpNode != nullptr)
		{
			tmp.addFirst(tmpNode->data);
			tmpNode = tmpNode->next;
		}
		return tmp;
	}
	CDlist operator*(const CDlist& second)
	{
		CDlist<T> result;
		if (this->size != 0 && second.size != 0)
		{
			Node* one = this->first;
			while (one != nullptr)
			{
				if (result.searchNode(one->data) == nullptr)
				{
					Node* two = second.first;
					while (two != nullptr)
					{
						if (one->data == two->data)
						{
							result.addLast(one->data);
							break;
						}
						two = two->next;
					}
				}
				one = one->next;
			}
		}
		return result;
	}
};