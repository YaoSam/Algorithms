#pragma once
#include <iostream>
#undef  TEMP
#define TEMP template <class T>
#undef re
#define re(i,n) for(unsigned int i=0;i<n;i++)
namespace ME
{
	TEMP struct node;
	TEMP class list;
	TEMP void Swap(list<T>& a, list<T>&b);
	TEMP
	struct node
	{
		T data;
		node<T>* next;
	public:
		node<T>(T const & D = T(), node<T>* N = NULL) : data(D), next(N){}
	};

	TEMP
	class list
	{
		node<T>* head, *last;
		unsigned int length;
		void check_last();
	public:
		list(T const a[] = NULL, unsigned int n = 0);
		list(list<T> const & other);
		~list();
		list<T>& operator=(list<T> const &other);
		unsigned int Length()const { return length; }
		void push_front(T const &x);
		void push_back(T const &x);
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
		class iterator :public std::iterator<std::forward_iterator_tag, T>
		{
			node<T>*const Head;
			node<T>* P;
		public:
			iterator(list<T>& other) :Head(other.head), P(other.head->next){}
			iterator(node<T>*const H, node<T>* p) :Head(H), P(p){}
			iterator& operator++()	{ P = P->next; return*this; }
			iterator operator++(int){ iterator ans(P); P = P->next; return ans; }
			T& operator*()const		{ return P->data; }
			T* operator->()const	{ return &(P->data); }
			bool isEnd()const		{ return P == NULL; }
			void reset()			{ P = Head->next; }
			bool operator==(const iterator& other)const{ return P == other.P; }
		};
		class const_iterator :public std::iterator<std::input_iterator_tag, T>
		{
			const node<T>* const Head;
			const node<T>* P;
		public:
			const_iterator(const list<T>& other) :Head(other.head), P(other.head->next){}
			const_iterator(const node<T>*const H, const node<T>* p) :Head(H), P(p){}
			const_iterator& operator++()	{ P = P->next; return *this; }
			const_iterator operator++(int)	{ const_iterator ans(P); P = P->next; return ans; }
			const T& operator*()const		{ return P->data; }
			const T* operator->()const		{ return &(P->data); }
			bool isEnd()const				{ return P == NULL; }
			void reset()					{ P = Head->next; }
			bool operator==(const const_iterator& other)const{ return P == other.P; }
		};
		class back_inserter :public std::iterator<std::forward_iterator_tag, T>
		{
			list<T>& me;
			node<T>* P;
		public:
			back_inserter(list<T>& other) :me(other), P(other.head->next){}
			back_inserter(list<T>& other, node<T>* p) :me(other), P(p), lenght(l){}
			back_inserter& operator=(const T&x)
			{
				me.push_back(x);
				return *this;
			}
			back_inserter& operator++()		{ P = P->next; return*this; }
			back_inserter operator++(int)	{ back_inserter ans(P); P = P->next; return ans; }
			T& operator*()const				{ return P->data; }
			T* operator->()const			{ return &(P->data); }
			bool isEnd()const				{ return P == nullptr; }
			void reset()					{ P = me.head->next; }
			bool operator==(const back_inserter& other)const { return P == other.P; }
		};
		//class front_inseter:public iterator
		//{
		//	list<T>*const me;
		//public:
		//	front_inseter(list<T>& other) :iterator(other.head->next), me(&other){}
		//	front_inseter& operator=(const T& x){ me->push_front(x); return *this; }
		//};
		iterator begin(){ return iterator(head, head->next); }
		iterator end(){ return iterator(head, nullptr); }
		const_iterator begin()const	{ return const_iterator(head, head->next); }
		const_iterator end()const	{ return const_iterator(head, nullptr); }
	};

}