#pragma once
#include <iostream>
#include <string>
#include "normal.h"

//只需要定义>

const int OriginalHeapSize = 100;
TEMP class Heap;
TEMP class MaxHeap;
TEMP class MinHeap;
TEMP void Swap(Heap<T>* a, Heap<T>* b);
TEMP
class Heap
{
protected:
	//记录最后一个节点
	int Current;
	unsigned int size;
	T *Data;
	//比较函数，对于堆来说多一个指针好像也差不多。
	bool (*compare)(T const & a, T const &b);
	//向下调整i节点。
	void Down(int i);
	//向上调整节点
	void Up(int i);
	void expend();//扩大两倍吧。
public:
	Heap(bool (*cmp)(T const & a, T const &b)) :
		size(OriginalHeapSize), 
		Data(new T[size]),
		Current(-1),
		compare(cmp){}
	//构造函数。通过不断向下调整节点实现。
	Heap(T const *data, unsigned int n, bool (*cmp)(T const & a, T const &b));
	//动态分配内存惯例要打以下三个函数。
	Heap(Heap<T> const & other) :
		Current(other.Current), 
		size(other.size),
		Data(new T[size]),
		compare(other.compare)
	{
		memcpy(Data, other.Data, sizeof(T)*(Current+1));
	}
	Heap<T>& operator=(Heap<T> const & other);
	virtual ~Heap(){ delete[] Data; }
	//插入
	void push(T const &X);
	//弹出节点。即删除
	T pop();
	bool isEmpty()const{ return Current < 0; }
	TEMP friend void Swap(Heap<T>* a, Heap<T>* b);
};
//////////////////////////////////////////////////////////////////////////
TEMP
class MaxHeap :public Heap < T >
{
	static bool MaxHeapCmp(T const &a, T const &b){ return a < b; }
public:
	MaxHeap() :Heap<T>(MaxHeapCmp){}
	MaxHeap(T const *data, unsigned int n);
	MaxHeap(MaxHeap<T> const & other);
	MaxHeap<T>& operator=(MaxHeap<T> const & other);
	virtual ~MaxHeap(){}
};
TEMP
class MinHeap :public Heap < T >
{
	static bool MinHeapCmp(T const &a, T const &b){ return a>b; }
public:
	MinHeap() :Heap<T>(MinHeapCmp){}
	MinHeap(T const *data, unsigned int n);
	MinHeap(MinHeap<T> const & other);
	MinHeap<T>& operator=(MinHeap<T> const & other);
	virtual ~MinHeap(){}
};

TEMP
void heapSort(T a[], unsigned int n);
