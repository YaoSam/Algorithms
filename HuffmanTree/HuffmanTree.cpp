#pragma once
#include "HuffmanTree.h"
namespace ME{
	TEMP
		HuffmanTree<T>::HuffmanTree(T const * Data, unsigned int n)
	{
		treeNode<T>** node = new treeNode<T>*[n], *left, *right;
		re(i, n)
		{
			*(node[i] = NodePool.pop()) = treeNode<T>(Data[i], 1);
		}
		Heap<treeNode<T>*> heap(node, n, treeNodeCmp);
		re(i, n - 1)
		{
			left = heap.pop(), right = heap.pop();
			treeNode<T>*temp = NodePool.pop();
			*temp = treeNode<T>(left->data + right->data, left->height + 1, left, right);
			heap.push(temp);
		}
		root = heap.pop();
		delete[] node;
	}
	TEMP
		HuffmanTree<T>::HuffmanTree(HuffmanTree<T> const & other) :
		NormalTree<T>(other)
	{}
	TEMP
		HuffmanTree<T>& HuffmanTree<T>::operator=(HuffmanTree<T> const & other)
	{
		NormalTree<T>:: = (other);
		return *this;
	}
}
