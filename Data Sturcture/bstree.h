#pragma once
#include "btree.h"

TEMP
class bstree :public NormalTree < T >
{
	using Tree<T>::root;
protected:
	treeNode<T>* FindRightNext(const treeNode<T>* a)const;
	treeNode<T>* FindLeftNext(const treeNode<T>* a)const;
	virtual void Maintain(treeNode<T>* node, T const& x);
public:
	void insert(T const & x)override;
	bstree(T const a[] = NULL, unsigned int n = 0);
	virtual ~bstree(){}
	treeNode<T>* find(T const &x)const override;
	virtual void DelNode(T const &x);
	Mid<T> begin()const	{ return Mid<T>(this); }//用中序遍历的迭代器。
	Mid<T> end()const { return  Mid<T>(); }
	//void erase(T const & x);
};
