#pragma once
#include <iostream>
#include <memory>
#undef TEMP
#define TEMP template <class T>
#define re(i,n) for(unsigned int i=0;i<n;i++)
namespace ME{
	const int OriginQueueSize = 20;
	TEMP class queue;
	TEMP void Swap(queue<T> &a, queue<T>& b);
	TEMP
	class queue//不能用动态分配内存的元素
	{
		unsigned int front, rear, size;//front都指向数据，rear指向位置。
		std::allocator<T> m_allocator;
		T *data;
		void expend();
	public:
		queue() :front(0), rear(0), size(OriginQueueSize), data(m_allocator.allocate(size)){}
		queue(const queue<T>&other);
		queue<T>& operator=(const queue<T>&other);
		~queue() { m_allocator.deallocate(data, size); }
		void push(T const &x);
		T pop();
		void clear(){ front = rear = 0; }
		bool isEmpty()const{ return front == rear; }
		TEMP friend void swap(queue<T> &a, queue<T>& b);
	};
}