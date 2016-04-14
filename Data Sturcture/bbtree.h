#pragma once
#include "bstree.h"
#include "normal.cpp"

TEMP
class AVLtree :public bstree < T >
{
	int differ(treeNode<T>* node)const//计算左边高度-右边。平衡二叉树用。
	{
		return int(node->left ? node->left->height : 0) - int(node->right ? node->right->height : 0);
	}
	void RotateLL(treeNode<T>* node);
	void RotateRR(treeNode<T>* node);
	void RotateLR(treeNode<T>* node);
	void RotateRL(treeNode<T>* node);
	void Maintain(treeNode<T>* node, T const &x);
	int Height(const treeNode<T>* node)const{//用来Debug的。检查对height的维护
		return Max(((node->left) ? Height(node->left) : 0), ((node->right) ? Height(node->right) : 0)) +1;
	}
public:
	int H()const
	{
		return Height(root);
	}
	AVLtree(T const a[] = NULL, unsigned int n = 0);
	virtual ~AVLtree(){}
};


template<typename A,typename B>
struct SearchNode
{
	A index;
	B data;
	SearchNode(A const &index, B const  &data) :index(index), data(data){}
	bool operator>(const SearchNode<A, B>& other)const{
		return index > other.index;
	}
	bool operator==(const SearchNode<A, B>& other)const{
		return index == other.index;
	}
};
template<typename A, typename B>
std::ostream& operator<<(std::ostream& out, const SearchNode<A, B>& other);

template<typename A, typename B>
class SearchTree:public AVLtree<SearchNode<A,B>>
{
public:
	SearchTree(A const *Index = NULL, B const * Data = NULL, unsigned int n = 0);
	SearchTree(SearchTree<A, B> const *node,unsigned int n);
	treeNode<SearchNode<A,B>>* find(A const & index)const;
};