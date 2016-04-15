#pragma once
#include "normal2.h"
#include "normal.cpp"
#include <iostream>
const int OriginalSize = 10;
TEMP
class array
{
	T *data;
	int size;
	int top;
	void expend();
public:
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
	T operator[](unsigned int n)const;
	T& operator[](unsigned int n);
	void push(const T &one);
	int Top()const{ return top; }
	friend std::ostream& operator<<(std::ostream& out, const array<T>& other)
	{
		re(i, other.top + 1)
			out << other.data[i] << " ";
		return out << std::endl;
	}
};
