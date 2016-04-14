#pragma once
#include "stdafx.h"
#include "CppUnitTest.h"
using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

void debug(const char * errorInfo)
{
	Logger::WriteMessage(errorInfo);
	Assert::Fail();
}
namespace UnitTest
{		
	TEST_CLASS(UnitTest_Tree)
	{
	public:
		TEST_METHOD(Test_AVLtree)
		{
			try
			{
				srand(int(time(NULL)));
				int a[10000];
				unsigned int SizeOfTest = 1000;
				re(i, SizeOfTest)
					a[i] = rand() % SizeOfTest;
				AVLtree<int> one(a, SizeOfTest);
				AVLtree<int> two(one);//测试复制构造
				one = two;//测试赋值函数
				Qsort(a, 0, SizeOfTest - 1);
				Mid_iterator<int> iterM(&one);
				re(i, SizeOfTest)
				{
					if (*iterM != a[i])
						debug("不一致");
					++iterM;
				}
				re(i, SizeOfTest - 5)
				{
					one.DelNode(a[i]);
					if (one.NodeNum() != SizeOfTest - i - 1)
						debug("删除后节点不对");
					//if ((int)one.height() > maxHeight_bbtree(SizeOfTest - i - 1))
					//	debug("高度不对");
				}
			}
			catch (const char *err){ debug(err); }
		}
		TEST_METHOD(Test_BStree)
		{
			try
			{
				srand(int(time(NULL)));
				int a[10000];
				unsigned int SizeOfTest = 200;
				re(i, SizeOfTest)
					a[i] = rand() % (SizeOfTest / 2);
				bstree<int> one(a, SizeOfTest);
				Qsort(a, 0, SizeOfTest - 1);
				Mid_iterator<int> iterM(&one);
				re(i, SizeOfTest)
				{
					if (*iterM != a[i])
						debug("不一致\n");
					++iterM;
				}
				re(i, SizeOfTest)
				{
					one.DelNode(a[i]);
					if (SizeOfTest - i - 1 != one.NodeNum())
						debug("测试删除节点后节点数目出错");
				}
			}
			catch (const char *err){ debug(err); }
		}
		TEST_METHOD(Test_DiscreteSegTree)
		{
			try
			{
				clock_t time1, time2;
				char str[1000];
				Segment Seg[100];
				int SizeofTest = 50000;
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
				//简单测试
			{
				int num[100] = { 35, 25, 15, 15, 10 };
				int check[100] = { 100, 40, 60, 15, 25, 25, 35, 10, 15 };
				HuffmanTree<int> one(num, 5);
				Level_iterator<int> iterL(&one);
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
				Pre_iterator<int> iterP(&two);
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
				unsigned int SizeOfTest = 2000;
				stack<int> one, two;
				re(i, SizeOfTest)
					one.push(rand() % SizeOfTest);
				two = one;
				Swap(one, two);
				Swap(one, two);
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
				Swap(a, b);
				Swap(a, b);
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
					one.RearInsert(a[i]);
				re(i, SizeOfTest)
					one.HeadInsert(a[i]);
				list<int> two = one;
				one = two;
				Swap(one, two);
				Swap(one, two);
				one.resetPointer();
				std::stringstream ss;
				std::string str;
				re(i, SizeOfTest)
				{
					if (*one.pointer != a[SizeOfTest - i - 1])
						debug("前序插入错了");
					++one.pointer;
				}
				re(i, SizeOfTest)
				{
					if (*one.pointer != a[i])
						debug("后序插入错了");
					++one.pointer;
				}
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
				MaxHeap<int> one(abc, SizeOfTest);
				MaxHeap<int> two = one;
				one = two;
				Swap(&one, &two);
				Swap(&two, &one);
				memcpy(bcd, abc, SizeOfTest*sizeof(int));
				heapSort(abc, SizeOfTest);
				Qsort_MaxToMin(bcd, 0, SizeOfTest - 1);
				re(i, SizeOfTest)
					if (abc[i] != bcd[i])
						debug("排序不匹配");
				re(i, SizeOfTest)
					if (one.pop() != bcd[i])
						debug("pop不匹配");
			}
			catch (const char * err){ debug(err); }
		}
	};
}