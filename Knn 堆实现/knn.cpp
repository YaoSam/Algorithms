#pragma once
#include "C:\Users\Sam\OneDrive\C++\数据结构汇总\Data Structure\Data Sturcture\normal.cpp"

TEMP
void Down(int i, int Current, T Heap[])
{
	int next = 2 * i + 1;
	while (next <= Current)
	{
		//不断向下跟较大的节点交换。
		if (next + 1 <= Current && (Heap[next]<Heap[next + 1]))
			next++;
		if (!(Heap[next]<Heap[i]))
			Swap(Heap[next], Heap[i]);
		else break;
		i = next;
		next = next * 2 + 1;
	}
}


TEMP
void initial(int n, T Heap[])
{
	re(i, n / 2 + 2) //从0 到 n/2+1
		Down(n / 2 + 1 - i, n, Heap); //从n/2+1 到 0
}


TEMP
void Qsort_knn(T a[], int left, int right, int k)
{
	while (true)
	{
		int l = left, r = right;
		T mid = a[left + rand() % (right - left + 1)];
		do
		{
			while (a[l] < mid)l++;
			while (a[r] > mid)r--;
			if (l <= r)
				Swap(a[l++], a[r--]);
		} while (l <= r);
		//相对于快排增加了一个筛选条件。只要left，right跨越k才继续。，因为(left+right)/2当right=left+1时是left，所以right等号必须取
		if (left < k&&r >= k)
			right = r;
		else if (l < k&&right >= k)
			left = l;
		else 
			return;
	}
}

TEMP
void heapSort_knn(int n, int k, T Data[])
{
	if (k >= n)return;
	initial(k, Data);//建堆。大小为k
	re(j,n-k)
	{
		if (Data[j + k]<Data[0])//比较最大元素
		{
			Swap(Data[0], Data[j + k]);//更新最大值
			Down(0, k - 1, Data);//从上到下维护堆
		}
	}
}

TEMP
void super_knn(int n, int k, T data[])
{
	int left = 0, right = n - 1,count=int(log2(n))/2;
	if (k>n / 10)
		re(i, count)
	{
		int l = left, r = right;
		T mid = data[left + rand() % (right - left + 1)];
		do
		{
			while (data[l] < mid)l++;
			while (data[r] > mid)r--;
			if (l <= r)
				Swap(data[l++], data[r--]);
		} while (l <= r);
		if (left < k&&r >= k)
			right = r;
		else if (l < k&&right >= k)
			left = l;
		else
			return;
	}
	heapSort_knn(right - left + 1, /*元素数目*/k - left,/*剩余的前k个*/data + left);/*新的起始位置*/
}
