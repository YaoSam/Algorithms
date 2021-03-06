#pragma once
#include "stdafx.h"
#include "CppUnitTest.h"
#include <algorithm>
using namespace std;
using namespace ME;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	static long long FIB[100];
	void debug(const char * errorInfo)
{
	Logger::WriteMessage(errorInfo);
	Assert::Fail();
}
	TEST_CLASS(Bstree)
	{
	public:
		TEST_METHOD(Test_BStree)
		{
			try
			{
				srand(int(time(NULL)));
				int a[10000];
				unsigned int SizeOfTest = 2000;
				re(i, SizeOfTest)
					a[i] = rand() % (SizeOfTest / 2);
				bstree<int> one(a, SizeOfTest);
				Qsort(a, 0, SizeOfTest - 1);
				Mid<int> iterM(one);
				re(i, SizeOfTest)
				{
					if (*iterM != a[i])
						debug("不一致\n");
					++iterM;
				}
			}
			catch (const char *err){ debug(err); }
		}
		TEST_METHOD(BiDirectionIterator)
		{
			srand(int(time(NULL)));
			int a[10000];
			unsigned int SizeOfTest = 10000;
			re(i, SizeOfTest)
				a[i] = rand() % SizeOfTest;
			AVLtree<int> one(a, SizeOfTest);
			Qsort(a, 0, SizeOfTest - 1);
			Mid<int> iterM(one);
			int current_i = 0;
			re(i,100)
			{
				int j = rand() % (SizeOfTest - current_i);
				current_i += j;
				re(k, j)
					++iterM;
				j = rand() % (current_i);
				current_i -= j;
				re(k, j)
					--iterM;
				if (a[current_i] != *(iterM))
					debug("不一致");
			}
		}
		TEST_METHOD(bstree_Find)
		{
			srand(int(time(NULL)));
			int a[10000];
			unsigned int SizeOfTest = 10000;
			re(i, SizeOfTest)
				a[i] = rand() % SizeOfTest;
			bstree<int> one(a, SizeOfTest);
			sort(a, a + SizeOfTest);
			for (auto i : a)
			{
				auto iter = one.Find(i);
				if (*iter != i)
					debug("找不到！");
			}
		}
		TEST_METHOD(Delete_Node)
		{
			try {
				srand(int(time(NULL)));
				int a[500], b[500];
				unsigned int SizeOfTest = 500;
				re(i, SizeOfTest)
					a[i] = rand() % (100*SizeOfTest);
				bstree<int> one(a, SizeOfTest);
				char message[100] = "";
				re(i, SizeOfTest)
				{
					one.DelNode(a[SizeOfTest - i - 1]);
					if (SizeOfTest - i - 1 != one.NodeNum())
					{
						sprintf(message, "%d\n", i);
						Logger::WriteMessage(message);
						debug("测试删除节点后节点数目出错");
					}
					memcpy(b, a, sizeof(int)*(SizeOfTest));
					sort(b, b + SizeOfTest - i - 1);
					Mid<int> iter(one);
					if (!equal(one.begin(), one.end(), b))
					{
						char ans[10];
						sprintf(ans, "%d", i);
						Logger::WriteMessage(ans);
						debug("顺序不对");
					}

				}
			}
			catch (const char* a) { debug(a); }
		}
	};
	TEST_CLASS(AVLTree)
	{
		long long Fibonacci(int n)const
		{
			if (FIB[n] > 0) return FIB[n];
			return FIB[n] = (n == 1 || n == 0) ? n : Fibonacci(n - 1) + Fibonacci(n - 2);
		}

		int minHeight_bbtree(int n)const
		{
			int i = 0;
			for (; n > 0; i++)
				n -= (1 << i);
			return i;
		}
		int maxHeight_bbtree(int n)const//最大高度为：F(H+2)-1<=n<=F(H+3)-1
		{
			int height = 0;
			while ((Fibonacci(height + 2) - 1) <= n)	height++;
			return height - 1;
		}
	public:
		TEST_METHOD(Test_AVLtree)
		{
			try
			{
				srand(int(time(NULL)));
				int a[10000];
				unsigned int SizeOfTest = 10000;
				re(i, SizeOfTest)
					a[i] = rand() % SizeOfTest;
				AVLtree<int> one(a, SizeOfTest);
				AVLtree<int> two(one);//测试复制构造
				one = two;//测试赋值函数
				Qsort(a, 0, SizeOfTest - 1);
				if (!equal(one.begin(), one.end(), a))
					debug("不一致");
			}
			catch (const char *err){ debug(err); }
		}
		TEST_METHOD(avltree_delete_node)
		{
			srand(int(time(NULL)));
			int a[5000],b[5000];
			unsigned int SizeOfTest = 500;
			re(test_turn, 10)
			{
				re(i, SizeOfTest)
					a[i] = rand() % SizeOfTest;
				AVLtree<int> one(a, SizeOfTest);
				re(i, SizeOfTest - 3)
				{
					one.DelNode(a[SizeOfTest - i - 1]);
					memcpy(b, a, sizeof(a));
					sort(b, b + SizeOfTest - i - 1);
					if (one.NodeNum() != SizeOfTest - i - 1)
						debug("删除后节点不对");
					if (!equal(one.begin(), one.end(), b))
					{
						char ans[10];
						sprintf(ans, "%d", i);
						Logger::WriteMessage(ans);
						debug("顺序不对");
					}
					if ((int)one.H() > maxHeight_bbtree(SizeOfTest - i - 1))
					{
						char ans[10];
						sprintf(ans, "%d,高度为：%d，%d\n", i,one.height(),one.H());
						Logger::WriteMessage(ans);
						debug("高度不对");
					}
				}
			}
		}
	};
	TEST_CLASS(UnitTest_Tree)
	{
	public:
		TEST_METHOD(Test_DiscreteSegTree)
		{
			try
			{
				clock_t time1, time2;
				char str[1000];
				Segment Seg[100];
				int SizeofTest = 20000;
				Seg[0] = Segment(0, 3);
				Seg[1] = Segment(11, 20);
				Seg[2] = Segment(3, 4);
				Seg[3] = Segment(0, SizeofTest);
				time1 = clock();
				DiscreteSegTree one(Seg, 4);
				time2 = clock();
				sprintf_s(str, "%d\n", int(time2 - time1));
				Logger::WriteMessage(str);
				time1 = clock();
				SegmentTree two(0, SizeofTest);
				time2 = clock();
				sprintf_s(str, "%d\n", int(time2 - time1));
				Logger::WriteMessage(str);
				re(i, 4)
					two.insert(Seg[i]);
				Assert::AreEqual(two.count(), one.count());
			}
			catch (const char * err){ debug(err); }
		}
		TEST_METHOD(Test_HuffmanTree)
		{
			try
			{
				//简单测试
				int num[100] = { 35, 25, 15, 15, 10 };
				int check[100] = { 100, 40, 60, 15, 25, 25, 35, 10, 15 };
				HuffmanTree<int> one(num, 5);
				Level<int> iterL(one);
				re(i, 9)
				{
					if (*iterL != check[i])
						debug("对不上");
					++iterL;
				}
				//大规模测试
				int a[100000], b[100000]; unsigned int SizeOfTest = 10000;
				re(i, SizeOfTest)
					a[i] = rand() % SizeOfTest;
				HuffmanTree<int> two(a, SizeOfTest);
				unsigned int Count = two.NodeNum();
				if (Count != 2 * SizeOfTest - 1)
					debug("所有的点数目不对");
				Count = 0;
				Pre<int> iterP(two);
				while (!iterP.isEnd())
				{
					if (iterP()->Height() == 1)
						b[Count++] = *iterP;
					++iterP;
				}
				if (Count != SizeOfTest)
					debug("叶子节点的数目不对");
				Qsort(a, 0, SizeOfTest - 1);
				Qsort(b, 0, SizeOfTest - 1);
				re(i, SizeOfTest)
					if (a[i] != b[i])
						debug("叶子结点");
			}
			catch (const char *err){ debug(err); }
		}
	};
	TEST_CLASS(UnitTest2)
	{
	public:
		TEST_METHOD(Test_Stack)
		{
			try
			{
				srand(int(time(NULL)));
				int a[10000];
				unsigned int SizeOfTest = 200;
				stack<int> one, two;
				re(i, SizeOfTest)
					one.push(rand() % SizeOfTest);
				two = one;
				ME::swap(one, two);
				ME::swap(one, two);
				re(i, SizeOfTest)
					a[i] = one.pop();
				re(i, SizeOfTest)
					if (a[i] != two.pop())
						debug("对不上");
			}
			catch (const char *err){ debug(err); }
		}
		TEST_METHOD(Test_Queue)
		{
			try
			{
				srand(unsigned(time(NULL)));
				queue<int> a, b;
				unsigned int SizeOfTest = 1000;
				re(i, SizeOfTest)
					a.push(rand() % SizeOfTest);
				queue<int> c = a;
				re(i, 2)
				{
					while (!a.isEmpty())
						b.push(a.pop());
					while (!b.isEmpty())
						a.push(b.pop());
				}
				ME::swap(a, b);
				ME::swap(a, b);
				re(i, SizeOfTest)
					if (a.pop() != c.pop())
						debug("对不上了");
			}
			catch (const char *err){ debug(err); }
		}
		TEST_METHOD(Test_List)
		{
			try
			{
				srand(int(time(NULL)));
				int a[1000];
				unsigned int SizeOfTest = 200;
				re(i, SizeOfTest)
					a[i] = rand() % SizeOfTest;
				list<int> one(a, SizeOfTest);
				Qsort(a, 0, SizeOfTest - 1);
				re(i, SizeOfTest)//earse test
					one.delNode(a[i]);
				re(i, SizeOfTest)
					one.push_back(a[i]);
				re(i, SizeOfTest)
					one.push_front(a[i]);
				list<int> two = one;
				one = two;
				swap(one, two);
				swap(one, two);
			}
			catch (const char * err){ debug(err); }
		}
		TEST_METHOD(Test_MaxHeap)
		{
			try{
				unsigned int SizeOfTest = 1800;
				int abc[10000] = { 0 }, bcd[10000] = { 0 };
				re(i, SizeOfTest)
					abc[i] = rand() % SizeOfTest;
				MinHeap<int> one(abc, SizeOfTest);
				MinHeap<int> two = one;
				one = two;
				swap(one, two);
				swap(two, one);
				memcpy(bcd, abc, SizeOfTest*sizeof(int));
				ME::heapSort(abc, SizeOfTest);
				sort(bcd, bcd + SizeOfTest);
				re(i, SizeOfTest)
					if (abc[i] != bcd[i])
						debug("排序不匹配");
				re(i, SizeOfTest)
					if (one.pop() != bcd[i])
						debug("pop不匹配");
			}
			catch (const char * err){ debug(err); }
		}
		TEST_METHOD(Test_Array)
		{
			srand(int(time(NULL)));
			int a[1000];
			unsigned int SizeOfTest = 1000;
			re(i, SizeOfTest)
				a[i] = rand() % SizeOfTest;
			ME::array<int> one(a, 1000);
			//测试随机迭代器。
			sort(one.begin(), one.end());
			sort(a, a + SizeOfTest);
			re(i, SizeOfTest)
				if (a[i] != one[i])
					debug("排序出错");
			const ME::array<int> two(one);
			int i = 0;
			for (auto one:two)
				if (one != a[i++])
					debug("复制出错");
		}
	};
}