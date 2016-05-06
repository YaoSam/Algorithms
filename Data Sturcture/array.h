#pragma once
#include "normal.cpp"
#include <iostream>
#include <iterator>
namespace ME
{
	const int OriginalSize = 10;
	TEMP
	class array
	{
		T *data;
		int size;
		int top;
		void expend();
	public:
		//friend class array<T>::iterator;
		class iterator :public std::iterator<std::random_access_iterator_tag, T>
		{
			const T *root, *end;
			T* P;
		public:
			//下面5句与继承iterator等价。为了trait服务。
			//typedef std::random_access_iterator_tag iterator_category;
			//typedef T value_type;
			//typedef typename std::allocator<T>::difference_type difference_type;
			//typedef typename std::allocator<T>::const_pointer pointer;
			//typedef typename std::allocator<T>::const_reference reference;
			iterator(const T* r = nullptr, T *p = nullptr, const T* e = nullptr) :root(r), P(p), end(e){}
			iterator(array& Array) :root(Array.data), P(Array.data), end(Array.data + Array.top + 1){}
			void goFirst()						{ P = root; }
			bool isEnd()const					{ return P == end; }
			bool CheckRange()					{ return P >= root&&P < end; }
			T& operator*()const { return (*P); }
			iterator& operator++()		{ ++P; return *this; }
			iterator& operator--()		{ --P; return *this; }
			iterator operator++(int)		{ return iterator(root, P++, end); }
			iterator operator--(int)		{ return iterator(root, P--, end); }
			iterator operator+(const int & movement)const	{ return iterator(root, P + movement, end); }
			iterator operator-(const int & movement)const	{ return iterator(root, P - movement, end); }
			iterator& operator+=(const int & movement)	{ P += movement; return *this; }
			iterator& operator-=(const int & movement)	{ P -= movement; return *this; }
			int operator-(const iterator& other)const		{ return P - other.P; }
			bool operator==(const iterator& other)const	{ return P == other.P; }
			bool operator>(const iterator& other)const	{ return P > other.P; }
		};
		class const_iterator :public std::iterator<std::input_iterator_tag, const T>
		{
			T const * root, *end;
			const T* P;//不允许改变值。
		public:
			const_iterator(T* const r = nullptr, const T *p = nullptr, T*const e = nullptr) :root(r), P(p), end(e){}
			const_iterator(const array& Array) :root(Array.data), P(Array.data), end(Array.data + Array.top + 1){}
			void goFirst()						{ P = root; }
			bool isEnd()const					{ return P == end; }
			bool CheckRange()					{ return P >= root&&P < end; }
			const T& operator*()const			{ return (*P); }
			const_iterator& operator++()		{ ++P; return *this; }
			const_iterator& operator--()		{ --P; return *this; }
			const_iterator operator++(int)		{ return const_iterator(root, P++, end); }
			const_iterator operator--(int)		{ return const_iterator(root, P--, end); }
			const_iterator operator+(const int & movement)const	{ return const_iterator(root, P + movement, end); }
			const_iterator operator-(const int & movement)const	{ return const_iterator(root, P - movement, end); }
			const_iterator& operator+=(const int & movement)	{ P += movement; return *this; }
			const_iterator& operator-=(const int & movement)	{ P -= movement; return *this; }
			int operator-(const const_iterator& other)const		{ return P - other.P; }
			bool operator==(const const_iterator& other)const	{ return P == other.P; }
			bool operator>(const const_iterator& other)const	{ return P > other.P; }
		};
		array(unsigned int n) :
			size(n), top(-1)
		{
			data = new T[size];//天知道为什么要写在下面。
		}
		array() :
			size(OriginalSize), top(-1)
		{
			data = new T[size];
		}
		array(T const *D, unsigned int n) :
			top(int(n) - 1), size(n)
		{
			data = new T[size];
			memcpy(data, D, sizeof(T)*n);
		}
		array(const array<T>& other);
		array<T>& operator=(const array<T>& other);
		~array(){ delete[] data; }
		const T& operator[](unsigned int n)const
		{
			if (n >= size)throw "OUT OF SIZE!";
			return data[n];
		}
		T& operator[](unsigned int n)
		{
			if (n >= size)throw "OUT OF SIZE!";
			if (int(n) > top)top = n;
			return data[n];
		}
		void push(const T &one);
		const int& Top()const	{ return top; }
		const int& Size()const	{ return size; }
		iterator begin()		{ return iterator(*this); }
		const_iterator begin()const { return const_iterator(*this); }
		const_iterator cbegin()const{ return const_iterator(*this); }
		iterator end()			{ return iterator(nullptr, data + top + 1); }
		const_iterator end()const{ return const_iterator(nullptr, data + top + 1); }
		const_iterator cend()const	{ return const_iterator(nullptr, data + top + 1); }
		friend std::ostream& operator<<(std::ostream& out, const array<T>& other)
		{
			re(i, other.top + 1)
				out << other.data[i] << " ";
			return out << std::endl;
		}
		TEMP friend void swap(array<T>& a, array<T>& b);
	};

	TEMP
		using arr_iterator = typename array<T>::iterator;

}