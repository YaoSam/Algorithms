#pragma  once
#include "btree.h"
#include "ALL.h"
#include "normal.h"
#include "normal.cpp"
#include "normal2.h"
#include "normal2.cpp"
#include <algorithm>
#include <math.h>
using namespace std;
using namespace ME;
void TestOfArray()
{
	int a[1000] = { 0 };
	unsigned int SizeOfTest = 1000;
	re(i, SizeOfTest)
	{
		a[i] = rand() % SizeOfTest;
		//hello.push(a[i]);
	}
	const array<int> hello(a,SizeOfTest);
	//sort(hello.begin(), hello.end());
	for (const auto& i : hello)
	{
		cout << i << " ";
	}
	cout << endl;
	for (auto i : a)
		cout << i << " ";
	cout << endl;
}

void TestOfQueue()//修改后请通过该函数进行测试。
{
	srand(unsigned(time(NULL)));
	queue<int> a, b;
	unsigned int SizeOfTest = 100;
	re(i, SizeOfTest)
		a.push(rand() % 1000);
	queue<int> c = a;
	re(i, 1000)
	{
		while (!a.isEmpty())
			b.push(a.pop());
		while (!b.isEmpty())
			a.push(b.pop());
	}
	re(i, SizeOfTest)
		cout << a.pop() << " ";
	cout << endl;
	re(i, SizeOfTest)
		cout << c.pop() << " ";
	cout << endl;
}

void TestOfStack()
{
	srand(unsigned(time(NULL)));
	stack<int> a, b;
	unsigned int n = 10100;
	re(i, n)
		a.push(rand() % 1000);
	cout << a;
	while (!a.isEmpty())
		b.push(a.pop());
	a = b;
	re(i, n)
		cout << b.pop() << " ";
	cout << endl << a << endl;
}

void TestOfList()
{
	srand(int(time(NULL)));
	int a[1000];
	unsigned int SizeOfTest = 10;
	re(i, SizeOfTest)
		a[i] = rand() % 100;
	list<int> one(a, SizeOfTest);
	std::back_insert_iterator<list<int>> inserter(one);
	re(i, 5)
		inserter = i;
	cout << one;
	Qsort(a, 0, SizeOfTest - 1);
	auto ans = std::find(one.begin(), one.end(), a[6]);
	cout << *ans << endl;
	re(i, SizeOfTest)//earse test
	{
		one.delNode(a[i]);
		//cout << one << endl;
	}
	cout << one;
	re(i, SizeOfTest)
		one.push_back(rand() % 1000);
	cout << one;
	re(i, SizeOfTest)
		one.push_front(rand() % 1000);
	cout << one;
	const list<int> two = one;
	list < int > ::back_inserter iter(one);
	//iter.reset();
	//re(i, one.Length()-1)++iter;
	//auto fun = [](const int &temp){if (temp > 100)cout << temp << " "; };
	re(i,10) iter = 1000;
	//for_each(one.begin(), one.end(),fun);
	//for (auto& i : two)
	//{
	//	cout << i << " ";
	//}
	cout << endl;
	cout << one;
	const blist<int> Blist(one);
	//re(i, 10)Blist.push_back(123);
	cout << Blist;
	//for (const auto& i : two)
	//	Blist.push_front(i);
	for (auto & i : Blist)
		cout << i << " ";
	//Blist.erase(123);
	//for (const auto& i : two)
	//{
	//	Blist.DelNode(i);
	//	cout << Blist;
	//}
}


void TestOfBstree()
{
	srand(int(time(NULL)));
	int a[100000];
	unsigned int SizeOfTest =10000;
	re(i, SizeOfTest)
		a[i] = rand() % 100000;
	bstree<int> one(a, SizeOfTest);
	bstree<int> two;
	Swap(&one, &two);
	Swap(&two, &one);
	one.pre();
	one.mid();
	one.post();
	//bstree<int> another = one;
	//another.mid();
	//one = another;
	//one.mid();
	re(i, SizeOfTest)
	{
		treeNode<int>* temp = one.find(a[i]);
		if (temp == NULL)
			cout << "无法找到！" << endl;
	}
	cout << one.height() << endl;
	re(i, SizeOfTest)
		one.insert(a[i]);
	re(i, SizeOfTest)
	{
		//cout << a[i] << endl;
		one.DelNode(a[i]);
		//cout << one.NodeNum() << " ";
	}
}

void TestOfAVLTree()
{
	srand(int(time(NULL)));
	int a[100000];

	unsigned int SizeOfTest = 10000;
	re(i, SizeOfTest)
		a[i] = rand() % 10000;
	Qsort(a, 0, SizeOfTest - 1);
	AVLtree<int> one(a, SizeOfTest);
	AVLtree<int> two(one);
	one = two;
	//one.pre();
	//one.mid();
	//one.post();
	//one.print();
	re(i, SizeOfTest)
	{
		treeNode<int>* temp = one.find(a[i]);
		if (temp == NULL)
			cout << "无法找到！" << endl;
	}
	cout << "树高度：" << one.H() << endl;
	cout << "最大高度：" << maxHeight_bbtree(SizeOfTest) << endl;
	cout << "最低高度：" << minHeight_bbtree(SizeOfTest) << endl;
	cout << "节点数：" << one.NodeNum() << endl;
	cout << "当前高度的最少节点：" << Fibonacci(one.height()+2)-1 << endl;
	cout << endl;
	//re(i, SizeOfTest)
	//	one.insert(rand() % 10000);
	//cout << "树高度：" << one.Height() << endl;
	//cout << "节点数：" << one.NodeNum() << endl;
	re(i, SizeOfTest)
		one.insert(a[i]);
	re(i, SizeOfTest)
	{
		one.DelNode(a[i]);
		//if (one.NodeNum() != SizeOfTest - i - 1)
			//cout << "错了！" << endl;
	}
	//cout << endl;
	//cout << "树高度：" << one.Height() << endl;
	//cout << "节点数：" << one.NodeNum() << endl;
}

void TestOfIterator()
{
	srand(int(time(NULL)));
	int a[10000];
	unsigned int SizeOfTest = 1000;
	re(i, SizeOfTest)
		a[i] = rand() % 10000;
	const AVLtree<int> one(a, SizeOfTest);
	for (auto& i : one)
		cout << i << " ";
	cout << endl;
	one.mid();
	sort(a, a + SizeOfTest);
	re(i, SizeOfTest)
		cout << a[i] << " ";
	cout << endl;
	Mid<int> wer(&one);
	int current_i = 0;
	re(i,100)
	{
		cout << i << " ";
		int j = rand()%(SizeOfTest - current_i);
		current_i += j;
		cout << current_i << " ";
		re(k, j)
			++wer;
		j = rand() % (current_i);
		current_i -= j;
		cout << current_i << " ";
		re(k, j)
			--wer;
		if (a[current_i] != *(wer))
			cout << "ERROR" << endl;
	}
	//--wer;
	//while (!wer.isEnd())
	//{
	//	cout << *wer << " ";
	//	--wer;
	//}
	cout << endl;
	//one.pre();
}

void TestOfHeap()
{
	unsigned int SizeOfTest= 1800;
	int abc[10000] = { 0 }, bcd[10000] = { 0 };
	re(i, SizeOfTest)
	{
		abc[i] = rand() % 10000;
		//cout << abc[i] << " ";
	}
	cout << endl;
	memcpy(bcd, abc, SizeOfTest*sizeof(int));
	heapSort(abc, SizeOfTest);
	Qsort_MaxToMin(bcd, 0, SizeOfTest - 1);
	re(k, SizeOfTest)
	{
		if (bcd[k] != abc[k])
		{
			re(i, SizeOfTest)
				cout << abc[i] << ' ';
			cout << endl;
			re(i, SizeOfTest)
				cout << bcd[i] << ' ';
			cout << endl;
			break;
		}
	}
}

void Test()
{
	try{
		cout<<"测试动态数组"<<endl;
		TestOfArray();
		//cout << "测试栈" << endl;
		//TestOfStack();
		//cout << "测试队列" << endl;
		//TestOfQueue();
		cout << "测试链表" << endl;
		TestOfList();
		//cout << "\n测试排序二叉树" << endl;
		//TestOfBstree();
		//cout << "\n测试平衡二叉树" << endl;
		//TestOfAVLTree();
		cout << "\n测试迭代器" << endl;
		TestOfIterator();
		//cout << "\n测试堆" << endl;
		//TestOfHeap();

	}
	catch (const char *a){
		cout << a << endl;
	}
}
