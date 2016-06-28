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
			//node[i] = new treeNode<T>(Data[i], 1);
		}
		Heap<treeNode<T>*> heap(node, n, treeNodeCmp);
		re(i, n - 1)
		{
			left = heap.pop(), right = heap.pop();
			treeNode<T>*temp = NodePool.pop();
			*temp = treeNode<T>(left->data + right->data, left->height + 1, NULL, left, right);
			heap.push(temp);
			//heap.push(new treeNode<T>(left->data + right->data, left->height + 1, NULL, left, right));
		}
		root = heap.pop();
		//NodePool.push(node);
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
