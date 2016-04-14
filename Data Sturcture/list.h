#pragma once
#include <iostream>
#include <time.h>
#undef  TEMP
#define TEMP template <class T>
#undef re
#define re(i,n) for(unsigned int i=0;i<n;i++)

TEMP struct node;
TEMP class list;
TEMP void Swap(list<T>& a, list<T>&b);
TEMP 
struct node
{
	T data;
	node<T>* next;
public:
	node<T>(T const & D=T(), node<T>* N = NULL) : data(D), next(N){}
};

TEMP 
class list
{
	node<T>* head;
	unsigned int length;
	node<T>* last()const;
public:
	list(T const a[] = NULL, unsigned int n = 0);
	list(list<T> const & other);
	~list();
	list<T>& operator=(list<T> const &other);
	unsigned int Length()const { return length; }
	void HeadInsert(T const &x);
	void RearInsert(T const &x);
	node<T>* find(T const &x);
	void delNode(T const &x);//删除一个x的点
	void erase(T const & x);//删除所有为x的点。
	TEMP friend void Swap(list<T>& a, list<T>&b);
	friend std::ostream& operator<<(std::ostream& out, list<T> const & other)
	{
		node<T>* temp = other.head->next;
		while (temp != NULL)
		{
			out << temp->data << " ";
			temp = temp->next;
		}
		return out << std::endl;
	}
	void resetPointer(){ pointer = head->next; }
	class list_iterator{
	private:
		node<T>* P;
		friend list < T > ;
	public:
		list_iterator(node<T>* p) :P(p){}
		node<T>* operator++();
		list_iterator& operator=(node<T>* p){ P = p; return *this; }
		T operator*()const;
		bool isEnd(){ return P == NULL; }
		void reset(){ P = head; }
	}pointer;
};