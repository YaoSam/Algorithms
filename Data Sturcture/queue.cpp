#pragma once
#include "queue.h"
namespace ME{
	TEMP
		void queue<T>::expend()
	{
		T* temp = m_allocator.allocate(size * 2);
		//这里交换位置使得数据顺序。
		if (front > rear)
		{
			std::uninitialized_copy_n(data + front, size - front, temp + front);
			std::uninitialized_copy_n(data, rear, temp + size);
			rear += size;
		}
		else
			std::uninitialized_copy_n(data + front, rear - front, temp + front);
		m_allocator.deallocate(data, size);
		size *= 2;
		data = temp;
	}

	TEMP
		queue<T>::queue(const queue<T>&other) :
		front(other.front),
		rear(other.rear),
		size(other.size),
		data(m_allocator.allocate(size))
	{
		std::uninitialized_copy_n(other.data, size, data);
	}

	TEMP
		queue<T>& queue<T>::operator=(const queue<T>&other)
	{
		if (this == &other)return *this;
		m_allocator.deallocate(data, size);
		front = other.front;
		rear = other.rear;
		size = other.size;
		data = m_allocator.allocate(size);
		std::uninitialized_copy_n(other.data, size, data);
		return *this;
	}
	TEMP
		void queue<T>::push(T const &x)
	{
		if ((rear + 1) % size == front)//只能牺牲一个位置了。
			expend();
		m_allocator.construct(data + rear, x);
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

}