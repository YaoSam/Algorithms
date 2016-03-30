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
void heapSort_knn(int n, int k, T Data[])
{
	if (k >= n)return;
	initial(k, Data);//建立k个元素的堆

	int i,next;
	re(j,n-k)
	{
		if (Data[j + k]<Data[0])
		{
			Swap(Data[0], Data[j + k]);
			i = 0;
			//Down(0, k - 1, Data);
			next = 2 * i + 1;
			while (next <= k-1)
			{
				//不断向下跟较大的节点交换。
				if (next + 1 <= k-1 && (Data[next]<Data[next + 1]))
					next++;
				if (!(Data[next]<Data[i]))
					Swap(Data[next], Data[i]);
				else break;
				i = next;
				next = next * 2 + 1;
			}
		}
		//push(temp1, k - 1, Data);	//取一下一个元素放入堆
		//temp1 = Data[k+i+1];		//储存下一个位置
		//Data[k+i+1]=pop(k, Data);	//将下一个位置放最大值
	}
	//push(temp1, k - 1, Data);//取最后一个元素放入堆
	//Data[k] = pop(k, Data);//将第k+1个位置放最大值
}


TEMP
void _Qsort_knn(T a[], int left, int right, int k, int count)
{
	if (!(left <= k&&right >= k))return;
	if (count < 0)
	{
		heapSort_knn(right - left + 1, /*元素数目*/k - left,/*剩余的前k个*/a + left);/*新的起始位置*/
		return;
	}
	T mid = a[(left + right) / 2];
	int l = left, r = right;
	do
	{
		while (a[l] < mid)l++;
		while (a[r] > mid)r--;
		if (l <= r)
			Swap(a[l++], a[r--]);
	} while (l <= r);
	if (r > left)	_Qsort_knn(a, left, r, k, count - 1);
	if (l < right)	_Qsort_knn(a, l, right, k, count - 1);
}

TEMP
void super_knn(int n, int k, T data[])
{
	_Qsort_knn(data, 0, n - 1, k, floor(log10(n))/2);
}

