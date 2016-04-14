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
#include "SegmentTree.h"
#include <sstream>
using namespace std;
#undef re
#define re(i,n) for(unsigned int i=0;i<n;i++)
#define DEBUG
	unsigned int num[1000000];
void test()
{
	unsigned int SizeOfTest=100;
	SegmentTree one(0,SizeOfTest);
	one.print();
	re(i, SizeOfTest)
	{
		int a = rand()%SizeOfTest;
		int b = rand() % SizeOfTest;
		if (a > b)Swap(a, b);
		Segment Seg(a, b);
		cout << Seg << endl;
		one.insert(Seg);	
		num[i] = one.count();
		printf("Count: %d\n", one.count());
	}	

	re(i, SizeOfTest)
	{
		int a = rand() % SizeOfTest;
		int b = rand() % SizeOfTest;
		if (a > b)Swap(a, b);
		Segment Seg(a, b);
		one.del(Seg);	
		num[i] = one.count();
		printf("Count: %d\n", one.count());
	}

}

int main()
{
	clock_t BeginTime = clock();
	srand(unsigned(time(NULL)));
#ifdef DEBUG
	FILE *input, *output; //没用的指针... ...
	freopen_s(&input, "in.txt", "r", stdin);
	freopen_s(&output, "out.txt", "w", stdout);
#endif
	clock_t time1;
	//test();
	Segment Seg[100];
	Seg[0] = Segment(0, 3);
	Seg[1] = Segment(11, 20);
	Seg[2] = Segment(3, 4);
	Seg[3] = Segment(101,2000000000);
	time1 = clock();
	DiscreteSegTree one(Seg, 4);
	cout << one.count() << endl;
	one.del(Seg[3]);
	cout<<one.count()<<endl;
	one.insert(Seg[3]);
	cout << one.count() << endl;
	cout << endl << "运行时间：" << clock() - BeginTime << endl;
#ifndef DEBUG
	system("pause");
#endif // !DEBUG
	return 0;
}