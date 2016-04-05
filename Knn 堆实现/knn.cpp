#pragma once
#include "C:\Users\Sam\OneDrive\C++\���ݽṹ����\Data Structure\Data Sturcture\normal.cpp"

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
void initial(int n, T Heap[])
{
	re(i, n / 2 + 2) //��0 �� n/2+1
		Down(n / 2 + 1 - i, n, Heap); //��n/2+1 �� 0
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
		//����ڿ���������һ��ɸѡ������ֻҪleft��right��Խk�ż���������Ϊ(left+right)/2��right=left+1ʱ��left������right�Ⱥű���ȡ
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
	initial(k, Data);//���ѡ���СΪk
	re(j,n-k)
	{
		if (Data[j + k]<Data[0])//�Ƚ����Ԫ��
		{
			Swap(Data[0], Data[j + k]);//�������ֵ
			Down(0, k - 1, Data);//���ϵ���ά����
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
	heapSort_knn(right - left + 1, /*Ԫ����Ŀ*/k - left,/*ʣ���ǰk��*/data + left);/*�µ���ʼλ��*/
}
