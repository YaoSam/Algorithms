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
	void expend()
	{
		T *temp = new T[size*2];
		memcpy(temp, data, sizeof(T)*(top+1));
		size *= 2;
		delete[] data;
		data = temp;
	}
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
	array(const array<T>& other) :
		size(other.size), top(other.top)
	{
		data = new T[size];
		memcpy(data, other.data, sizeof(T)*(top+1));
	}
	array& operator=(const array<T>& other)
	{
		if (size < other.size)
		{
			delete[] data;
			size = other.size;
			data = new T[size];
		}
		top = other.top;
		memcpy(data, other.data, sizeof(T)*(top+1));
		return *this;
	}
	~array(){ delete[] data; }
	T operator[](unsigned int n)const
	{
		if (n >= size||n>top)throw "OUT OF SIZE!";
		return data[n];
	}
	T& operator[](unsigned int n)
	{
		while (n >= size)expend();
		if (int(n) > top)top = n;
		return data[n];
	}
	void push(const T &one)
	{
		if (top == size - 1)expend();
		data[++top] = one;
	}
};
