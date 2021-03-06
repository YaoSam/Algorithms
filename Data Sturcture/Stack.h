#pragma once

#include <iostream>
#include <memory>
#undef TEMP
#define TEMP template <class T>
#define re(i,n) for(unsigned int i=0;i<n;i++)
namespace ME{
	const int OriginSize = 10;

	TEMP class stack;
	TEMP void Swap(stack<T> &a, stack<T> &b);
	TEMP
	class stack//不能用于动态分配内存的元素。
	{
		int top, size;
		std::allocator<T> m_allocator;
		T *data;
		void expend();
	public:
		stack() :top(-1), size(OriginSize), data(m_allocator.allocate(size)){}
		stack(const stack<T>&other);
		stack<T>& operator=(const stack<T>& other);
		~stack(){ m_allocator.deallocate(data,size); }
		void push(T const & x);
		T pop()							{ return data[top--]; };
		void clear()					{ top = -1; }
		T topData()const				{ return data[top]; };//返回顶端元素
		unsigned int Number()const		{ return unsigned int(top + 1); }
		int Top()const					{ return top; }//返回栈大小
		bool isEmpty()const				{ return top < 0; }
		const T& operator[](unsigned int n)const { return data[n]; }
		friend std::ostream& operator<<(std::ostream &out, stack<T> const & other)
		{
			re(i, unsigned(other.top + 1))
				out << other.data[i] << " ";
			return out << std::endl;
		}
		TEMP friend void swap(stack<T> &a, stack<T> &b);
	};
}