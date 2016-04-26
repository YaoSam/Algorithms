#pragma once
#include <iostream>
#include <string>
#include "normal.h"
#include <memory>
//ֻ��Ҫ����>
namespace ME 
{
	const int OriginalHeapSize = 100;
	TEMP class Heap;
	TEMP class MaxHeap;
	TEMP class MinHeap;
	TEMP void Swap(Heap<T>* a, Heap<T>* b);
	TEMP
		class Heap
	{
	protected:
		//��¼���һ���ڵ�
		int Current;
		unsigned int size;
		std::allocator<T> m_Allocator;
		T *Data;
		//�ȽϺ��������ڶ���˵��һ��ָ�����Ҳ��ࡣ
		bool(*compare)(T const & a, T const &b);
		//���µ���i�ڵ㡣
		void expend();//���������ɡ�
	public:
		Heap(bool(*cmp)(T const & a, T const &b)) :
			size(OriginalHeapSize),
			Data(m_Allocator.allocate(OriginalHeapSize)),
			Current(-1),
			compare(cmp) {}
		Heap(T const *data, unsigned int n, bool(*cmp)(T const & a, T const &b));
		//��̬�����ڴ����Ҫ����������������
		Heap(Heap<T> const & other) :
			Current(other.Current),
			size(other.size),
			Data(m_Allocator.allocate(size)),
			compare(other.compare)
		{
			std::uninitialized_copy_n(other.Data, Current + 1, Data);
		}
		Heap<T>& operator=(Heap<T> const & other);
		virtual ~Heap() { m_Allocator.deallocate(Data, size); }
		//����
		void push(T const &X);
		//�����ڵ㡣����ɾ��
		T pop();
		T const& Top()const { return Data[Current]; }
		bool isEmpty()const { return Current < 0; }
		TEMP friend void Swap(Heap<T>* a, Heap<T>* b);
	};
	//////////////////////////////////////////////////////////////////////////
	TEMP
		class MaxHeap :public Heap < T >
	{
		static bool MaxHeapCmp(T const &a, T const &b) { return a < b; }
	public:
		MaxHeap() :Heap<T>(MaxHeapCmp) {}
		MaxHeap(T const *data, unsigned int n);
		MaxHeap(MaxHeap<T> const & other);
		MaxHeap<T>& operator=(MaxHeap<T> const & other);
		virtual ~MaxHeap() {}
	};
	TEMP
		class MinHeap :public Heap < T >
	{
		static bool MinHeapCmp(T const &a, T const &b) { return a > b; }
	public:
		MinHeap() :Heap<T>(MinHeapCmp) {}
		MinHeap(T const *data, unsigned int n);
		MinHeap(MinHeap<T> const & other);
		MinHeap<T>& operator=(MinHeap<T> const & other);
		virtual ~MinHeap() {}
	};

	TEMP
		void heapSort(T *a, unsigned int n);
}