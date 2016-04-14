#pragma once
#include "heap.h"
#undef  re
#define re(i,n) for(unsigned int i=0;i<n;i++)

TEMP void Heap<T>::Down(int i)
{
	int next = 2 * i + 1;
	while (next <= Current)
	{
		//不断向下跟较大的节点交换。
		if (next + 1 <= Current&&compare(Data[next], Data[next + 1]))
			next++;
		if (!compare(Data[next], Data[i]))
			Swap(Data[next], Data[i]);
		else break;
		i = next;
		next = next * 2 + 1;
	}
	return;
}

TEMP void Heap<T>::Up(int i)
{
	if (i > Current)	throw "越界";
	while (i != 0 && compare(Data[(i - 1) >> 1], Data[i]))
	{
		//(i-1)/2代表其父亲节点。
		Swap(Data[(i - 1) >> 1], Data[i]);
		//不断向上回溯放到合适位置。
		i = (i - 1) >> 1;
	}
}

TEMP void Heap<T>::expend()
{
	size *= 2;
	T* temp = new T[size];
	memcpy(temp, Data, (Current + 1)*sizeof(T));
	delete Data;
	Data = temp;
}

TEMP Heap<T>::Heap(T const *data, unsigned int n, bool(*cmp)(T const & a, T const &b)) :
Current(n - 1),
size(n),
Data(new T[size]),
compare(cmp)
{
	memcpy(Data, data, n*sizeof(T));
	re(i, n / 2 + 2) //从0 到 n/2+1
		Down(n / 2 + 1 - i); //从n/2+1 到 0
}

TEMP Heap<T>& Heap<T>::operator=(Heap<T> const & other)
{
	if (this == &other)return *this;
	delete[] Data;
	size = other.size;
	Data = new T[other.size];
	Current = other.Current;
	memcpy(Data, other.Data, sizeof(T)*(Current+1));
	return *this;
}

TEMP void Swap(Heap<T>* a, Heap<T>* b)
{
	Swap(a->Current, b->Current);
	Swap(a->compare, b->compare);
	Swap(a->size, b->size);
	Swap(a->Data, b->Data);
	return;
}

TEMP void Heap<T>::push(T const &X)
{
	if (Current >= int(size - 1))
		expend();
	//直接放在底部。
	Data[++Current] = X;
	//向上维护堆。
	Up(Current);
}

TEMP T Heap<T>::pop()
{
	if (Current == -1)	throw"堆为空。不能弹出。";
	//弹出堆顶
	T ans = Data[0];
	//取最后一个元素放在堆顶
	Data[0] = Data[Current--];
	//向下维护堆
	Down(0);
	return ans;
}

//////////////////////////////////////////////////////////////////////////
TEMP MaxHeap<T>::MaxHeap(T const *data, unsigned int n) :Heap<T>(data, n, MaxHeapCmp) {}
TEMP MinHeap<T>::MinHeap(T const *data, unsigned int n) : Heap<T>(data, n, MinHeapCmp) {}
TEMP MaxHeap<T>::MaxHeap(MaxHeap<T> const & other) :Heap<T>(other){}
TEMP MinHeap<T>::MinHeap(MinHeap<T> const & other) : Heap<T>(other){}
TEMP MaxHeap<T>& MaxHeap<T>::operator=(MaxHeap<T> const & other){
	Heap<T>::operator =(other);
	return *this;
}
TEMP MinHeap<T>& MinHeap<T>::operator=(MinHeap<T> const & other){
	Heap<T>::operator =(other);
	return *this;
}
//堆排序，随便打一下而已。堆建好了就两行的事。从大到小
TEMP void heapSort(T *a, unsigned int n)
{
	MaxHeap<T> one(a, n);
	re(i, n)a[i] = one.pop();
	return;
}
