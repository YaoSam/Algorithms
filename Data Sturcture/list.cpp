#pragma  once
#include "list.h"
namespace ME
{
	TEMP
		list<T>::list(T const a[] /* = NULL */, unsigned int n /* = 0 */) :
		head(new node<T>),
		length(n)
	{
		node<T>* temp = head;
		re(i, n - 1)
			temp = (temp->next = new node<T>(a[i]));
		if (n - 1 >= 0)
			last = temp->next = new node<T>(a[n - 1]);
		return;
	}

	TEMP
		list<T>::list(list<T> const & other) :
		head(new node<T>),
		length(other.length),
		last(head)
	{
		node<T>* othertemp = other.head->next, *temp = head;
		while (othertemp != NULL)
		{
			temp->next = new node<T>(othertemp->data);
			temp = temp->next;
			othertemp = othertemp->next;
		}
		check_last();
		return;
	}

	TEMP
		list<T>::~list()
	{
		node<T>* temp = head;
		while (head->next != NULL)
		{
			head = temp->next;
			delete temp;
			temp = head;
		}
		delete temp;
	}

	TEMP
		list<T>& list<T>::operator=(list<T> const & other)
	{
		if (this == &other)return *this;
		node<T>* temp = head;
		node<T>* othertemp = other.head->next;
		while (head->next != NULL)
		{
			head = temp->next;
			delete temp;
			temp = head;
		}
		delete temp;
		last = temp = head = new node < T > ;
		while (othertemp != NULL)
		{
			temp->next = new node<T>(othertemp->data);
			temp = temp->next;
			othertemp = othertemp->next;
		}
		length = other.length;
		check_last();
		return *this;
	}

	TEMP
		void list<T>::push_front(T const &x)
	{
		node<T>* temp = head->next;
		head->next = new node<T>(x, temp);
		length++;
		if (last->next != nullptr)
			last = last->next;
		return;
	}

	TEMP
		void list<T>::check_last()
	{
		while (last->next != NULL)
			last = last->next;
	}

	TEMP
		void list<T>::push_back(T const &x)
	{
		last->next = new node<T>(x);
		last = last->next;
		length++;
	}

	TEMP
		node<T>* list<T>::find(T const &x)
	{
		node<T>* temp = head->next;
		while (temp != NULL)
		{
			if (temp->data == x)
				break;
		}
		return temp;//找不到的时候就是NULL
	}

	TEMP
		void list<T>::delNode(T const &x)
	{
		node<T>* temp = head, *delP = NULL;
		while (temp->next)
		{
			if (temp->next->data == x)
			{
				if (last == temp->next)last = temp;
				delP = temp->next;
				temp->next = temp->next->next;
				delete delP;
				length--;
				break;//跟下面就一个差别。
			}
			else temp = temp->next;
		}
		return;
	}

	TEMP void Swap(list<T>& a, list<T>&b)
	{
		Swap(a.head, b.head);
		Swap(a.length, b.length);
		return;
	}

	TEMP
		void list<T>::erase(T const & x)
	{
		node<T>* temp = head, *delP = NULL;
		while (temp->next)
		{
			if (temp->next->data == x)
			{
				delP = temp->next;
				temp->next = temp->next->next;
				delete delP;
				length--;
			}
			else temp = temp->next;
		}
		return;
	}
}