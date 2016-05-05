#pragma once
#include "btree.cpp"
#include "heap.cpp"
#include "list.cpp"
#include "array.cpp"
#include "queue.cpp"
#include "stack.cpp"

namespace ME
{
	TEMP
		void swap(NormalTree<T>& a, NormalTree<T>& b)
	{
		Swap(a.root, b.root);
	}

	TEMP
		void swap(Heap<T> &a, Heap<T> &b)
	{
		Swap(a.Current, b.Current);
		Swap(a.size, b.size);
		Swap(a.compare, b.compare);
		Swap(a.Data, b.Data);
	}

	TEMP
		void swap(list<T>& a, list<T>&b)
	{
		Swap(a.head, b.head);
		Swap(a.last, b.last);
		Swap(a.length, b.length);
	}

	TEMP
		void swap(blist<T>& a, blist<T>&b)
	{
		Swap(a.head, b.head);
		Swap(a.last, b.last);
		Swap(a.length, b.length);
	}

	TEMP
		void swap(array<T>& a, array<T>& b)
	{
		Swap(a.size, b.size);
		Swap(a.top, b.top);
		Swap(a.data, b.data);
	}

	TEMP 
		void swap(queue<T> &a, queue<T>& b)
	{
		Swap(a.front, b.front);
		Swap(a.rear, b.rear);
		Swap(a.size, b.size);
		Swap(a.data, b.data);
	}

	TEMP
		void swap(stack<T> &a, stack<T> &b)
	{
		Swap(a.size, b.size);
		Swap(a.top, b.top);
		Swap(a.data, b.data);
	}
}