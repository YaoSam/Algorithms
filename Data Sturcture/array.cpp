#pragma once
#include "array.h"
TEMP void array<T>::expend()
{
	T *temp = new T[size * 2];
	memcpy(temp, data, sizeof(T)*(top + 1));
	size *= 2;
	delete[] data;
	data = temp;
}
TEMP array<T>::array(const array<T>& other) :
size(other.size), top(other.top)
{
	data = new T[size];
	memcpy(data, other.data, sizeof(T)*(top + 1));
}
TEMP array<T>& array<T>::operator=(const array<T>& other)
{
	if (size < other.size)
	{
		delete[] data;
		size = other.size;
		data = new T[size];
	}
	top = other.top;
	memcpy(data, other.data, sizeof(T)*(top + 1));
	return *this;
}
TEMP T array<T>::operator[](unsigned int n)const
{
	if (n >= size || n>top)throw "OUT OF SIZE!";
	return data[n];
}
TEMP T& array<T>::operator[](unsigned int n)
{
	while (n >= size)expend();
	if (int(n) > top)top = n;
	return data[n];
}
TEMP void array<T>::push(const T &one)
{
	if (top == size - 1)expend();
	data[++top] = one;
}