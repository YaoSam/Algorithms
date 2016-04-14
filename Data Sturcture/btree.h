#pragma once
#include <iostream>
#include <time.h>
#include "Stack.cpp"
#include "queue.cpp"
#include "normal.cpp"
#include "normal2.h"
#include <math.h>
#define re(i,n) for(unsigned int i=0;i<n;i++)


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
};
