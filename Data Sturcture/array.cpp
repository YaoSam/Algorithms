#pragma once
#include "array.h"
namespace ME
{
	TEMP void array<T>::expend()
	{
		T *temp = m_allocator.allocate(size * 2);
		std::uninitialized_copy_n(data, top + 1, temp);
		m_allocator.deallocate(data, size);
		size *= 2;
		data = temp;
	}
	TEMP array<T>::array(const array<T>& other) :
		size(other.size),
		top(other.top),
		data(m_allocator.allocate(size))
	{
		std::uninitialized_copy_n(other.data, top+1, data);
	}
	TEMP array<T>& array<T>::operator=(const array<T>& other)
	{
		if (this == &other)return *this;
		if (size < other.size)
		{
			m_allocator.deallocate(data, size);
			size = other.size;
			m_allocator.allocate(data, size);
		}
		top = other.top;
		std::uninitialized_copy_n(other.data, top + 1, data);
		return *this;
	}

	TEMP void array<T>::push(const T &one)
	{
		if (top == size - 1)expend();
		data[++top] = one;
	}

}
