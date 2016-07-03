/*
*　　　　　　　　┏┓　　　┏┓+ +
*　　　　　　　┏┛┻━━━┛┻┓ + +
*　　　　　　　┃　　　　　　　┃ 　
*　　　　　　　┃　　　━　　　┃ ++ + + +
*　　　　　　 ████━████ ┃+
*　　　　　　　┃　　　　　　　┃ +
*　　　　　　　┃　　　┻　　　┃
*　　　　　　　┃　　　　　　　┃ + +
*　　　　　　　┗━┓　　　┏━┛
*　　　　　　　　　┃　　　┃　　　　　　　　　　　
*　　　　　　　　　┃　　　┃ + + + +
*　　　　　　　　　┃　　　┃　　　　Code is far away from bug with the animal protecting　　　　　　　
*　　　　　　　　　┃　　　┃ + 　　　　神兽保佑,代码无bug　　
*　　　　　　　　　┃　　　┃
*　　　　　　　　　┃　　　┃　　+　　　　　　　　　
*　　　　　　　　　┃　 　　┗━━━┓ + +
*　　　　　　　　　┃ 　　　　　　　┣┓
*　　　　　　　　　┃ 　　　　　　　┏┛
*　　　　　　　　　┗┓┓┏━┳┓┏┛ + + + +
*　　　　　　　　　　┃┫┫　┃┫┫
*　　　　　　　　　　┗┻┛　┗┻┛+ + + +
*/
#include <iostream>
#include <string>
#include <time.h>
#include <algorithm>
#include "../Data Sturcture/normal.cpp"
using namespace std;
#undef re
#define re(i,n) for(unsigned int i=0;i<n;i++)
#define DEBUG

template<class T>
void InsertSort(T* arr, unsigned int num)
{
	static T key;
	static int i;
	for (int j = 0; j < num; j++)
	{
		key = arr[j];
		i = j - 1;
		while (i >= 0 && arr[i]>key)
		{
			arr[i + 1] = arr[i];
			i--;
		}
		arr[i + 1] = key;
	}
}


TEMP
void Qsort(T a[], int left, int right)
{
	T mid = a[(left + right) / 2];
	int l = left, r = right;
	do
	{
		while (a[l] < mid)l++;
		while (a[r] > mid)r--;
		if (l <= r)
			swap(a[l++], a[r--]);
	} while (l <= r);
	if (r > left)		Qsort(a, left, r);
	if (l < right)	Qsort(a, l, right);
}

int arr[100000000], brr[100000000];
int main()
{
	clock_t BeginTime = clock();
	srand(unsigned(time(NULL)));
#ifdef DEBUG
	FILE *input, *output; //没用的指针... ...
	freopen_s(&input, "in.txt", "r", stdin);
	freopen_s(&output, "out.txt", "w", stdout);
#endif
	try {
		/*主函数*/
		unsigned int TestSize = 1000000;
		re(i, TestSize)
			arr[i] = brr[i] = rand() % TestSize;
		//InsertSort(arr, TestSize);
		clock_t a = clock();
		sort(brr, brr + TestSize);
		cout << clock() - a << endl;
		a = clock();
		Qsort(arr, 0, TestSize - 1);
		cout << clock() - a << endl;
		//re(i, TestSize)
		//	cout << arr[i] << " ";
		//cout << endl;
		//re(i, TestSize)
		//	cout << brr[i] << " ";
		cout << endl;
		if (!equal(arr, arr + TestSize, brr))
			cout << "That is NOT EQUAL!!!" << endl;

	}
	catch (const char * error) { cout << error << endl; }
	cout << "运行时间：" << clock() - BeginTime << endl;
#ifndef DEBUG
	system("pause");
#endif // !DEBUG
	return 0;
}