#pragma once
#include "queue.h"

TEMP
void queue<T>::ApplyMem()
{
	T* temp = new T[size * 2];
	//这里交换位置使得数据顺序。
	if (front > rear)
	{
		memcpy(temp + front, data + front, (size - front)*sizeof(T));
		memcpy(temp + size , data, (rear)*sizeof(T));//因为此时一般是满的，所以不用考虑太多。
		rear += size;
	}
	else memcpy(temp + front, data + front, (rear - front)*sizeof(T));
	size *= 2;
	delete[] data;
	data = temp;
}

TEMP
queue<T>::queue(const queue<T>&other) :
front(other.front),
rear(other.rear),
size(other.size)
{
	data = new T[other.size];
	memcpy(data, other.data, sizeof(T)*size);
}

TEMP
queue<T>& queue<T>::operator=(const queue<T>&other)
{
	if (this = &other)return *this;
	front = other.front;
	rear = other.rear;
	size = other.size;
	data = new T[other.size];
	memcpy(data, other.data, sizeof(T)*size);
	return *this;
}
TEMP 
void queue<T>::push(T const &x)
{
	if ((rear + 1) % size == front)//只能牺牲一个位置了。
		ApplyMem();
	data[rear] = x;
	rear = (rear + 1) % size;
}

TEMP 
T queue<T>::pop()
{
	if (front == rear)
		throw "Empty Queue, failed queue.pop()";
	int tempfront = front;
	front = (front + 1) % size;
	return data[tempfront];
}

TEMP void Swap(queue<T> &a, queue<T>& b)
{
	Swap(a.front, b.front);
	Swap(a.rear, b.rear);
	Swap(a.size, b.size);
	Swap(a.data, b.data);
	return;
}
