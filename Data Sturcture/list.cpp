#pragma  once
#include "list.h"

TEMP
list<T>::list(T const a[] /* = NULL */, unsigned int n /* = 0 */) :
head(new node<T>),
length(n)
{
	node<T>* temp=head; 
	re(i, n)
		temp = (temp->next = new node<T>(a[i]));
	return;
}

TEMP
list<T>::list(list<T> const & other):
head(new node<T>),
length(other.length)
{
	node<T>* othertemp = other.head->next,*temp=head;
	while (othertemp != NULL)
	{
		temp->next = new node<T>(othertemp->data);
		temp = temp->next;
		othertemp = othertemp->next;
	}
	return;
}

TEMP 
list<T>::~list()
{
	node<T>* temp=head;
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
	temp=head = new node < T > ;
	while (othertemp != NULL)
	{
		temp->next = new node<T>(othertemp->data);
		temp = temp->next;
		othertemp = othertemp->next;
	}
	length = other.length;
	return *this;
}

TEMP
void list<T>::HeadInsert(T const &x)
{
	node<T>* temp = head->next;
	head->next = new node<T>(x, temp);
	length++;
	return;
}

TEMP
node<T>* list<T>::last()const
{
	node<T>* temp = head;
	while (temp->next != NULL)
		temp = temp->next;
	return temp;
}

TEMP
void list<T>::RearInsert(T const &x)
{
	last()->next = new node<T>(x);
	length++;
}

TEMP
node<T>* list<T>::find(T const &x)
{
	node<T>* temp=head->next;
	while (temp!=NULL)
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
	node<T>* temp = head,*delP=NULL;
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

TEMP
typename list<T>::list_iterator& list<T>::list_iterator::operator++()
{
	if (P== NULL)
		throw "List iterator out of range\n";
	P = P->next;
	return *this;
}
TEMP
typename list<T>::list_iterator list<T>::list_iterator::operator++(int)
{
	list_iterator ans(this);
	if (P == NULL)
		throw "List iterator out of range\n";
	P = P->next;
	return ans;
}
TEMP
T& list<T>::list_iterator::operator*()const
{
	if (P == NULL)
		throw "List iterator out of range\n";
	return P->data;
}

