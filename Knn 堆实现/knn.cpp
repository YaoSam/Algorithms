#include "knn.h"

TEMP
void Down(int i, int Current, T Heap[])
{
	int next = 2 * i + 1;
	while (next <= Current)
	{
		//�������¸��ϴ�Ľڵ㽻����
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
		//(i-1)/2�����丸�׽ڵ㡣
		Swap(Heap[(i - 1) >> 1], Heap[i]);
		//�������ϻ��ݷŵ�����λ�á�
		i = (i - 1) >> 1;
	}
}

TEMP
void initial(int n, T Heap[])
{
	re(i, n / 2 + 2) //��0 �� n/2+1
		Down(n / 2 + 1 - i, n, Heap); //��n/2+1 �� 0
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
	//ȡ���һ��Ԫ�ط��ڶѶ�
	Heap[0] = Heap[Current--];
	//����ά����
	Down(0,Current,Heap);
	return temp;
}

TEMP
void Qsort_knn(T a[], int left, int right, int k)
{
	//����ڿ���������һ��ɸѡ������ֻҪleft��right��Խk�ż�����
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
	initial(k, Data);//����k��Ԫ�صĶ�

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
				//�������¸��ϴ�Ľڵ㽻����
				if (next + 1 <= k-1 && (Data[next]<Data[next + 1]))
					next++;
				if (!(Data[next]<Data[i]))
					Swap(Data[next], Data[i]);
				else break;
				i = next;
				next = next * 2 + 1;
			}
		}
		//push(temp1, k - 1, Data);	//ȡһ��һ��Ԫ�ط����
		//temp1 = Data[k+i+1];		//������һ��λ��
		//Data[k+i+1]=pop(k, Data);	//����һ��λ�÷����ֵ
	}
	//push(temp1, k - 1, Data);//ȡ���һ��Ԫ�ط����
	//Data[k] = pop(k, Data);//����k+1��λ�÷����ֵ
}


TEMP
void _Qsort_knn(T a[], int left, int right, int k, int count)
{
	if (!(left <= k&&right >= k))return;
	if (count < 0)
	{
		heapSort_knn(right - left + 1, /*Ԫ����Ŀ*/k - left,/*ʣ���ǰk��*/a + left);/*�µ���ʼλ��*/
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

