#pragma once
#include "normal2.h"
#include "normal.cpp"
#include <iostream>
#include <iterator>
const int OriginalSize = 10;
TEMP
class array
{
	T *data;
	int size;
	int top;
	void expend();
public:
	friend class array_iterator;
	class array_iterator
	{
		const T *root,*end;
		T* pointer;
	public:
		array_iterator(T* r=nullptr,T *p=nullptr,T* e=nullptr) :root(r), pointer(p),end(e){}
		array_iterator(array& Array) :root(Array.data),pointer(Array.data),end(Array.data+Array.top+1){}
		void goFirst(){ pointer = root; }
		bool isEnd()const { return pointer == end; }
		bool CheckRange(){ return pointer >= root&&pointer < end; }
		T& operator*()const
		{
			return (*pointer); 
		}
		typename array_iterator& operator++()
		{
			++pointer; 
			return *this; 
		}
		typename array_iterator& operator--()
		{
			--pointer;
			return *this;
		}
		typename array_iterator operator+(const int & movement)const//没有边界检查哟~
		{
			return array_iterator(root, pointer + movement, end);
		}
		typename array_iterator operator-(const int & movement)const
		{
			return array_iterator(root, pointer - movement, end);
		}
		typename array_iterator& operator+=(const int & movement)
		{
			pointer += movement;
			return *this;
		}
		typename array_iterator& operator-=(const int & movement)
		{
			pointer -= movement;
			return *this;
		}
		int operator-(const array_iterator& other)const
		{
			return pointer - other.pointer;
		}
		bool operator==(const array_iterator& other)const{ return pointer == other.pointer; }
	};
	array(unsigned int n) :
		size(n),top(-1)
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
	const int& Size()const { return size; }
	array_iterator begin(){ return array_iterator(*this); }
	array_iterator end(){ return array_iterator(nullptr,data+top+1); }
	friend std::ostream& operator<<(std::ostream& out, const array<T>& other)
	{
		re(i, other.top + 1)
			out << other.data[i] << " ";
		return out << std::endl;
	}
};

TEMP
using arr_iterator = typename array<T>::array_iterator;