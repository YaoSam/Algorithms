#pragma once
#include <iostream>
#include <time.h>
#include "Stack.cpp"
#include "queue.cpp"
#include "normal.cpp"
#include "normal2.h"
#include <iterator>
#define re(i,n) for(unsigned int i=0;i<n;i++)
#undef NULL
#define NULL nullptr

TEMP class NormalTree;
TEMP class FreeTree;
TEMP class bstree;
TEMP class AVLtree;
class SegmentTree;
TEMP class HuffmanTree;
TEMP
class treeNode
{
	friend class NormalTree < T > ;
	friend class FreeTree < T > ;
	friend class bstree < T > ;
	friend class AVLtree < T > ;
	friend class SegmentTree;
	friend class HuffmanTree < T > ;
protected:
	T data;
	unsigned int height;
	treeNode<T>* left, *right,*parent;
	unsigned int CheckHeight()//更新高度
	{
		return height = Max((left ? left->height : 0), (right ? right->height : 0)) + 1;
	}
	inline void leftlink(treeNode<T>* other);
	inline void rightlink(treeNode<T>* other);
	void Copy(treeNode<T>*& root,const treeNode<T>*  otherRoot);//模仿前序遍历实现的复制
	void Del(treeNode<T>*& root);//模仿后序遍历实现删除。
public:
	treeNode<T>(T const &x=T(), unsigned int h = 1,treeNode<T>*p = NULL, treeNode<T>* l = NULL, treeNode<T>* r = NULL ) :
		data(x),height(h),left(l),right(r),parent(p){}
	T Data()const{ return data; }
	treeNode<T>* Left()const{ return left; }
	treeNode<T>* Right()const{ return right; }
	treeNode<T>* Parent()const{ return parent; }
	unsigned int Height()const{ return height; }
};
TEMP void Swap(NormalTree<T>* a, NormalTree<T>* b);
TEMP
class NormalTree//这东西用来继承吧！
{
protected:
	treeNode<T>* root;
	class m_iterator
	{
	protected:
		treeNode<T>* pCurrent, *m_root;
	public:
		m_iterator(treeNode<T>* P, treeNode<T>* R) :pCurrent(P), m_root(R){}
		virtual ~m_iterator(){}
		T operator*()const;
		bool isEnd()const{ return pCurrent == NULL; }
		treeNode<T>* operator()()const{ return pCurrent; }
		virtual void goFirst() = 0;
		bool operator==(const m_iterator& other)const { return pCurrent == other.pCurrent; }
		bool operator!=(const m_iterator& other)const { return pCurrent != other.pCurrent; }
	};
public:
	class Pre_iterator :public m_iterator
	{
		stack<treeNode<T>*> Stack;
		using m_iterator::pCurrent;
		using m_iterator::m_root;
	public:
		Pre_iterator(const NormalTree<T>* const tree) :m_iterator(tree->Root(), tree->Root()){}
		void goFirst()override{ pCurrent = m_root; Stack.clear(); }
		const Pre_iterator& operator++();
		static Pre_iterator end()//返回终点的迭代器。
		{
			return Pre_iterator(nullptr, nullptr);
		}
		bool operator==(const Pre_iterator& other)const { return pCurrent == other.pCurrent; }
		bool operator!=(const Pre_iterator& other)const { return pCurrent != other.pCurrent; }
	};
	class Mid_iterator :public m_iterator
	{
		stack<treeNode<T>*> Stack;
		using m_iterator::pCurrent;
		using m_iterator::m_root;
		Mid_iterator(treeNode<T>* root, treeNode<T>* p) :m_iterator(p, root){}
	public:
		Mid_iterator(const NormalTree<T>* tree);
		void goFirst()override;
		const Mid_iterator& operator++();
		static Mid_iterator end()
		{
			return Mid_iterator(nullptr,nullptr);
		}
		bool operator==(const Mid_iterator& other)const { return pCurrent == other.pCurrent; }
		bool operator!=(const Mid_iterator& other)const { return pCurrent != other.pCurrent; }
	};

	class Post_iterator :public m_iterator 
	{
		stack<treeNode<T>*> Stack;
		using m_iterator::pCurrent;
		using m_iterator::m_root;
		Post_iterator(treeNode<T>* root, treeNode<T>* p) :m_iterator(p, root){}
	public:
		Post_iterator(const NormalTree<T>* const tree);
		void goFirst()override;
		const Post_iterator& operator++();
		bool operator==(const Post_iterator& other)const { return pCurrent == other.pCurrent; }
		bool operator!=(const Post_iterator& other)const { return pCurrent != other.pCurrent; }
	};
	class Level_iterator :public m_iterator
	{
		queue<treeNode<T>*> Queue;
		using m_iterator::pCurrent;
		using m_iterator::m_root;
		Level_iterator(treeNode<T>* root, treeNode<T>* p) :m_iterator(p, root){}
	public:
		Level_iterator(const NormalTree<T>* const tree) :m_iterator(tree->Root(), tree->Root()){}
		void goFirst()override
		{
			pCurrent = m_root;
			Queue.clear();
		}
		const Level_iterator& operator++();
		static Level_iterator end()
		{
			return Level_iterator(nullptr, nullptr);
		}
		bool operator==(const Level_iterator& other)const { return pCurrent == other.pCurrent; }
		bool operator!=(const Level_iterator& other)const { return pCurrent != other.pCurrent; }
	};
public:
	NormalTree(T const & x,unsigned int h=1) :root(new treeNode<T>(x, h)){}
	NormalTree(treeNode<T>* r = NULL) :root(r){}
	NormalTree(NormalTree<T> const & other);
	NormalTree<T>& operator=(NormalTree<T> const & other);
	virtual ~NormalTree();
	unsigned int height(){ return root->height; }
	unsigned int NodeNum()const;
	void pre()const;
	void mid()const;
	void post()const;
	virtual void print()const;
	virtual treeNode<T>* find(T const & x)const;
	virtual void insert(T const & x) = 0;
	treeNode<T>* Root()const{ return root; }
	TEMP friend void Swap(NormalTree<T>* a, NormalTree<T>* b);
	Pre_iterator pre_begin()const	{ return Pre_iterator(this); }
	Mid_iterator mid_begin()const	{ return Mid_iterator(this); }
	Post_iterator post_begin()const	{ return Post_iterator(this); }
	Level_iterator level_begin()const{ return Level_iterator(this); }
};
