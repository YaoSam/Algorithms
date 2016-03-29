#include "knn.h"

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
void Up(int i, int Current, T Heap[])
{
	while (i != 0 && (Heap[(i - 1) >> 1] < Heap[i]))
	{
		//(i-1)/2代表其父亲节点。
		Swap(Heap[(i - 1) >> 1], Heap[i]);
		//不断向上回溯放到合适位置。
		i = (i - 1) >> 1;
	}
}

TEMP
void initial(int n, T Heap[])
{
	re(i, n / 2 + 2) //从0 到 n/2+1
		Down(n / 2 + 1 - i, n, Heap); //从n/2+1 到 0
}

TEMP
void push(T const &x, int Current, T Heap[])
{
	Heap[++Current] = x;
	Up(Current,Current,Heap);
}

TEMP
T pop(int Current, T Heap[])
{
	T temp = Heap[0];
	//取最后一个元素放在堆顶
	Heap[0] = Heap[Current--];
	//向下维护堆
	Down(0,Current,Heap);
	return temp;
}

TEMP
void Qsort_knn(T a[], int left, int right, int k)
{
	//相对于快排增加了一个筛选条件。只要left，right跨越k才继续。
	if (!(left <= k&&right >= k))return;
	T mid = a[(left + right) / 2];
	int l = left, r = right;
	do
	{
		while (a[l] < mid)l++;
		while (a[r] > mid)r--;
		if (l <= r)
			Swap(a[l++], a[r--]);
	} while (l <= r);
	if (r > left)		Qsort_knn(a, left, r,k);
	if (l < right)	Qsort_knn(a, l, right,k);
}


TEMP
void knn(int n, int k, T Data[])
{
	if (k >= n)return;
	initial(k, Data);//建立k个元素的堆
	T temp1=Data[k],temp,max;
	re(i,n-k-1)
	{
		push(temp1, k - 1, Data);	//取一下一个元素放入堆
		temp1 = Data[k+i+1];		//储存下一个位置
		Data[k+i+1]=pop(k, Data);	//将下一个位置放最大值
	}
	push(temp1, k - 1, Data);//取最后一个元素放入堆
	Data[k] = pop(k, Data);//将第k+1个位置放最大值
}
