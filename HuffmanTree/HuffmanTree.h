#pragma once
#include "../Data Sturcture/heap.cpp"
#include "../Data Sturcture/btree.cpp"

TEMP
class HuffmanTree :public NormalTree < T > 
{
	static bool treeNodeCmp(treeNode<T>* const &a, treeNode<T>* const &b){ return a->Data() > b->Data(); }
public:
	HuffmanTree(T const * Data, unsigned int n);
	HuffmanTree(HuffmanTree<T> const & other);
	HuffmanTree<T>& operator=(HuffmanTree<T> const & other);
	virtual ~HuffmanTree(){}
	virtual void insert(T const & x){ throw "未定义插入函数"; }
};