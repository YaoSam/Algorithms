#pragma once
#include <iostream>
#undef  TEMP
#define TEMP template <class T>
#undef re
#define re(i,n) for(unsigned int i=0;i<n;i++)
namespace ME
{
	TEMP struct node;
	TEMP struct bnode;
	TEMP class list;
	TEMP class blist;
	TEMP void Swap(list<T>& a, list<T>&b);
	TEMP void Swap(blist<T>& a, blist<T>&b);
	TEMP
	struct node
	{
		T data;
		node<T>* next;
		node<T>(T const & D = T(), node<T>* N = NULL) : data(D), next(N){}
	};

	TEMP
	class list
	{
		node<T>* head, *last;
		unsigned int length;
		void check_last();
	public:
		typedef T value_type;
		list(T const a[] = NULL, unsigned int n = 0);
		list(list<T> const & other);
		list(blist<T> const& other);
		~list();
		list<T>& operator=(list<T> const &other);
		unsigned int Length()const { return length; }
		void push_front(T const &x);
		void push_back(T const &x)
		{
			last->next = new node<T>(x);
			last = last->next;
			length++;
		}
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
		template <class derive_iter>
		class base_iter
		{
		protected:
			node<T>* Head;
			node<T>* P;
		public:
			base_iter(list<T>& other):Head(other.head),P(other.head->next){}
			base_iter(node<T>* H, node<T>* p) :Head(H), P(p){}
			derive_iter& operator++()	{ P = P->next; return static_cast<derive_iter&>(*this); }
			derive_iter operator++(int) { derive_iter ans(*this); P = P->next; return ans; }
			T& operator*()				{ return P->data; }
			T* operator->()const		{ return &(P->data); }
			bool isEnd()const			{ return P == nullptr; }
			void reset()				{ P = Head->next; }
			bool operator==(const derive_iter& other)const { return P == other.P; }
		};
		class iterator:
			public base_iter<iterator>, 
			public std::iterator<std::forward_iterator_tag, T>
		{
		public:
			iterator(list<T>& other):base_iter<iterator>(other){}
			iterator(node<T>* H, node<T>* p):base_iter<iterator>(H,p){}
		};
		class const_iterator:public base_iter<const_iterator>, public std::iterator<std::input_iterator_tag, T>
		{
		public:
			const_iterator(list<T>& other):base_iter<const_iterator>(other){}
			const_iterator(node<T>* H, node<T>* p) :base_iter<const_iterator>(H, p) {}
			const T& operator*()	{ return P->data; }
			const T* operator->()	{ return &(P->data); }
		};
		class back_inserter:public base_iter<back_inserter>,public std::iterator<std::forward_iterator_tag,T>
		{
			list<T>& me;
		public:
			back_inserter(list<T>& other) :base_iter<back_inserter>(other),me(other) {}
			back_inserter(list<T>& other,node<T>* p) :base_iter<back_inserter>(other.head,p),me(other){}
			back_inserter& operator=(const T& x)
			{
				me.push_back(x);
				return *this;
			}
		};
		class front_inserter:public base_iter<front_inserter>,public std::iterator<std::forward_iterator_tag,T>
		{
			list<T>& me;
		public:
			front_inserter(list<T>& other) :base_iter<front_inserter>(other),me(other) {}
			front_inserter(list<T>& other,node<T>* p) :base_iter<front_inserter>(other.head,p),me(other){}
			front_inserter& operator=(const T& x)
			{
				me.push_front(x);
				return *this;
			}
		};
		iterator find(T const &x);
		iterator begin(){ return iterator(head, head->next); }
		iterator end(){ return iterator(head, nullptr); }
		const_iterator begin()const	{ return const_iterator(head, head->next); }
		const_iterator end()const	{ return const_iterator(head, nullptr); }
	};
	

	TEMP
	struct bnode
	{
		T data;
		bnode<T>* pre,*post;
		bnode(const T& data=T(), bnode<T>*Pre=nullptr, bnode<T>* Post=nullptr) :data(data), pre(Pre), post(Post){}
	};

	TEMP
	class blist
	{
		bnode<T>* head,*last;
		unsigned int length;
	public:
		typedef T value_type;
		blist(const T* a = nullptr, unsigned int n = 0);
		blist(const blist<T>& other);
		blist(const list<T>& other);
		~blist();
		blist<T>& operator=(const blist<T>& other);
		const unsigned int &Length()const{ return length; }
		void push_back(const T& x)
		{
			last->post = new bnode<T>(x, last);
			last = last->post;
			length++;
		}
		void push_front(const T& x);
		void DelNode(const T &x);
		void erase(const T& x);
		friend std::ostream& operator<<(std::ostream& out, const blist<T>& other)
		{
			bnode<T>* temp = other.head->post;
			while (temp)
			{
				out << temp->data << " ";
				temp = temp->post;
			}
			return out << std::endl;
		}
		template <class deri_iter>
		class base_iter
		{
		protected:
			bnode<T>* Head;
			bnode<T>* P;
		public:
			base_iter(blist<T>& other) :Head(other.head), P(other.head->post){}
			base_iter(bnode<T>*const H, bnode<T>* p) :Head(H), P(p){}
			deri_iter& operator++()	{ P = P->post; return static_cast<deri_iter&>(*this); }
			deri_iter operator++(int){ deri_iter ans(Head,P); P = P->post; return ans; }
			deri_iter& operator--() { P = P->pre; return static_cast<deri_iter&>(*this); }
			deri_iter operator--(int){ deri_iter ans(Head,P); P = P->pre; return ans; }
			T& operator*()const		{ return P->data; }
			T* operator->()const	{ return &(P->data); }
			bool isEnd()const		{ return P == NULL; }
			void reset()			{ P = Head->post; }
			bool operator==(const deri_iter& other)const{ return P == other.P; }
		};
		class iterator:public base_iter<iterator>,public std::iterator<std::bidirectional_iterator_tag, T>
		{
		public:
			iterator(blist<T>& other) :base_iter<iterator>(other) {}
			iterator(bnode<T>*const H, bnode<T>* p) :base_iter<iterator>(H,p) {}
		};
		class const_iterator :public base_iter<const_iterator>,public std::iterator<std::input_iterator_tag,T>
		{
		public:
			const_iterator(blist<T>& other) :base_iter<const_iterator>(other){}
			const_iterator(bnode<T>* H, bnode<T>* p) :base_iter<const_iterator>(H,p){}
			const T& operator*()const		{ return P->data; }
			const T* operator->()const		{ return &(P->data); }
		};
		iterator find(const T& x);
		const_iterator find(const T& x)const;
		iterator begin()			{ return iterator(head,head->post); }
		const_iterator begin()const	{ return const_iterator(head, head->post); }
		const_iterator cbegin()		{ return const_iterator(head, head->post); }
		iterator end()				{ return iterator(head,nullptr); }
		const_iterator end()const	{ return const_iterator(head, nullptr); }
		const_iterator cend()		{ return const_iterator(head, head); }
		friend void Swap(blist<T>& a, blist<T>& b);
	};
}