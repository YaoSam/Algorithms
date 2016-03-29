#include "C:\Users\Sam\OneDrive\C++\数据结构汇总\Data Structure\Data Sturcture\normal.cpp"
#include "C:\Users\Sam\OneDrive\C++\数据结构汇总\Data Structure\Data Sturcture\normal2.h"

struct Node
{
	float dis;
	int index;
	bool operator>(const Node& other)const
	{
		return dis > other.dis;
	}
};
TEMP
void Down(int i, int Current, T Heap[]);

TEMP
void Up(int i, int Current, T Heap[]);

TEMP
void initial(int Current, T Heap[]);

TEMP
void push(T const &x, int Current, T Heap[]);

TEMP
T pop(int Current, T Heap[]);

TEMP
void knn(int n, int k, T Data[]);


TEMP
void Qsort_knn(T a[], int left, int right, int k);