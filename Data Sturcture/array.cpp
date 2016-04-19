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

TEMP void array<T>::push(const T &one)
{
	if (top == size - 1)expend();
	data[++top] = one;
}