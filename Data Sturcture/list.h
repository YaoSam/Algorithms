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
	class iterator:public std::iterator<std::output_iterator_tag,T>
	{
		node<T>* P;
	public:
		iterator(const list<T>& other) :P(other.head->next){}
		iterator(node<T>* p) :P(p){}
		iterator& operator++()	{ P = P->next; return*this; }
		iterator operator++(int){ iterator ans(P); P = P->next; return ans; }
		T& operator*()const		{ return P->data; }
		T* operator->()const	{ return &(P->data); }
		bool isEnd()const		{ return P == NULL; }
		void reset()			{ P = head; }
		bool operator==(const iterator& other)const{ return P == other.P; }
	};
	class const_iterator:public std::iterator<std::input_iterator_tag,T>
	{
		const node<T>* P;
	public:
		const_iterator(const list<T>& other) :P(other.head->next){}
		const_iterator(const node<T>* p) :P(p){}
		const_iterator& operator++()	{ P = P->next; return *this; }
		const_iterator operator++(int)	{ const_iterator ans(P); P = P->next; return ans; }
		const T& operator*()const		{ return P->data; }
		const T* operator->()const		{ return &(P->data); }
		bool isEnd()const				{ return P == NULL; }
		void reset()					{ P = head; }
		bool operator==(const const_iterator& other)const{ return P == other.P; }

	};
	iterator begin(){ return iterator(head->next); }
	iterator end(){ return iterator(nullptr); }
	const_iterator begin()const	{ return const_iterator(head->next); }
	const_iterator end()const	{ return const_iterator(nullptr); }
};