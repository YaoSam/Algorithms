#pragma once
#include "heap.h"
#undef  re
#define re(i,n) for(unsigned int i=0;i<n;i++)

namespace ME
{
	namespace {
		TEMP
			void head_Down(int i, const int &Current, T* Data, bool(*cmp)(T const & a, T const &b))
		{
			int next = 2 * i + 1;
			while (next <= Current)
			{
				//不断向下跟较大的节点交换。
				if (next + 1 <= Current&&cmp(Data[next], Data[next + 1]))
					next++;
				if (!cmp(Data[next], Data[i]))
					Swap(Data[next], Data[i]);
				else break;
				i = next;
				next = next * 2 + 1;
			}
		}

		TEMP
			inline bool min_cmp(const T&a, const T&b) { return a < b; }
	}

	TEMP void Heap<T>::expend()
	{
		size *= 2;
		T* temp = m_Allocator.allocate(size);
		std::uninitialized_copy_n(Data, Current + 1, temp);
		m_Allocator.deallocate(Data, size);
		Data = temp;
	}

	TEMP Heap<T>::Heap(T const *data, unsigned int n, bool(*cmp)(T const & a, T const &b)) :
		Current(n - 1),
		size(n),
		Data(m_Allocator.allocate(size)),
		compare(cmp)
	{
		std::uninitialized_copy_n(data, n, Data);
		re(i, n / 2 + 2) //从0 到 n/2+1
			head_Down(n / 2 + 1 - i,Current,Data,compare); //从n/2+1 到 0
	}

	TEMP Heap<T>& Heap<T>::operator=(Heap<T> const & other)
	{
		if (this == &other)return *this;
		m_Allocator.deallocate(Data, size);
		size = other.size;
		Data = m_Allocator.allocate(other.size);
		Current = other.Current;
		std::uninitialized_copy_n(other.Data, Current + 1, Data);
		return *this;
	}

	TEMP void Heap<T>::push(T const &X)
	{
		if (Current >= int(size - 1))
			expend();
		//直接放在底部。
		m_Allocator.construct(Data + (++Current), X);
		//向上维护堆。
		int i = Current;
		while (i != 0 && compare(Data[(i - 1) >> 1], Data[i]))
		{
			//(i-1)/2代表其父亲节点。
			Swap(Data[(i - 1) >> 1], Data[i]);
			//不断向上回溯放到合适位置。
			i = (i - 1) >> 1;
		}
	}

	TEMP T Heap<T>::pop()
	{
		if (Current == -1)	throw"堆为空。不能弹出。";
		//弹出堆顶
		T ans = Data[0];
		//取最后一个元素放在堆顶
		Data[0] = Data[Current];
		m_Allocator.destroy(Data + (Current--));
		//向下维护堆
		head_Down(0,Current,Data,compare);
		return ans;
	}

	//////////////////////////////////////////////////////////////////////////
	TEMP MaxHeap<T>::MaxHeap(T const *data, unsigned int n) :Heap<T>(data, n, MaxHeapCmp) {}
	TEMP MinHeap<T>::MinHeap(T const *data, unsigned int n) : Heap<T>(data, n, MinHeapCmp) {}
	TEMP MaxHeap<T>::MaxHeap(MaxHeap<T> const & other) : Heap<T>(other) {}
	TEMP MinHeap<T>::MinHeap(MinHeap<T> const & other) : Heap<T>(other) {}
	TEMP MaxHeap<T>& MaxHeap<T>::operator=(MaxHeap<T> const & other) {
		Heap<T>::operator =(other);
		return *this;
	}
	TEMP MinHeap<T>& MinHeap<T>::operator=(MinHeap<T> const & other) {
		Heap<T>::operator =(other);
		return *this;
	}
	//堆排序，随便打一下而已。堆建好了就两行的事。从大到小


	TEMP void heapSort(T *a, unsigned int n)
	{
		int Current = n - 1;
		re(i, n / 2 + 2) //initialize heap
			head_Down(n / 2 + 1 - i,Current,a,min_cmp); //从n/2+1 到 0
		re(i,n-1)
		{
			Swap(a[0], a[Current--]);
			head_Down(0, Current, a,min_cmp);
		}
	}
}