#pragma once
#include "Stack.h"
namespace ME{
	TEMP
		void stack<T>::expend()
	{
		size *= 2;
		T *temp = new T[size];
		//re(i, top + 1)
		//temp[i] = data[i];
		memcpy(temp, data, sizeof(T)*(top + 1));
		delete[] data;
		data = temp;
	}

	TEMP
		stack<T>::stack(const stack<T>&other) :
		top(other.top),
		size(other.size),
		data(m_allocator.allocate(size))
	{
		//re(i, other.top+1) //暂时先不考虑动态分配内存的玩意了。
		//data[i] = other.data[i];
		std::uninitialized_copy_n(other.data, other.top + 1, data);
	}

	TEMP
		stack<T>& stack<T>::operator=(const stack<T>& other)
	{
		if (this == &other)return *this;
		delete[] data;
		top = other.top;
		size = other.size;
		data = m_allocator.allocate(size);
		//re(i, other.top+1)
		//data[i] = other.data[i];
		std::uninitialized_copy_n(other.data, top + 1, data);
		return *this;
	}
	TEMP
		void stack<T>::push(T const & x)
	{
		if (top == size - 1)
			expend();
		m_allocator.construct(data + (++top), x);
		//data[++top] = x;
	}
}