#include "freetree.h"
TEMP 
treeNode<T>* FreeTree<T>::leftinsert(T const &x,treeNode<T>* y_node )
{
	if (y_node == NULL)
		throw "空节点无法插入";
	if (y_node->left)
		throw "左节点非空，不能插入";
	return y_node->left = new treeNode<T>(x, y_node->height + 1, y_node);
}

TEMP
treeNode<T>* FreeTree<T>::rightinsert(T const &x, treeNode<T>* y_node)
{
	if (y_node == NULL)
		throw "空节点无法插入";
	if (y_node->right)
		throw "右节点非空，不能插入";
	return y_node->right = new treeNode<T>(x, y_node->height + 1, y_node);
}
