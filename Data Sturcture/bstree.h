#pragma once
#include "btree.h"

TEMP
class bstree :public NormalTree < T >
{
protected:
	treeNode<T>* FindRightNext(const treeNode<T>* a)const;
	treeNode<T>* FindLeftNext(const treeNode<T>* a)const;
	virtual void Maintain(treeNode<T>* node, T const& x);
public:
	virtual void insert(T const & x);
	bstree(T const a[] = NULL, unsigned int n = 0);
	virtual ~bstree(){}
	treeNode<T>* find(T const &x)const;
	virtual void DelNode(T const &x);
	typename NormalTree<T>::Mid_iterator begin()const{ return NormalTree<T>::Mid_iterator(this); }
	typename NormalTree<T>::Mid_iterator end()const	{ return  NormalTree<T>::Mid_iterator::end(); }
	//void erase(T const & x);
};