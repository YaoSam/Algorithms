#pragma once
#include "bbtree.h"
namespace ME{
	TEMP
		void AVLtree<T>::RotateLL(treeNode<T>* node,treeNode<T>* node_parent=NULL)
	{
		treeNode<T>* Root = node->left;
		if (node_parent==NULL)
			root = Root;
		else
		{
			if (node_parent->left == node)
				node_parent->left = Root;
			else
				node_parent->right = Root;
		}
		node->left = Root->right;
		Root->right = node;
		node->CheckHeight();
		Root->CheckHeight();
	}

	TEMP
		void AVLtree<T>::RotateRR(treeNode<T>* node, treeNode<T>* node_parent = NULL)
	{
		treeNode<T>* Root = node->right;
		if (node_parent == NULL)
			root = Root;
		else
		{
			if (node_parent->left == node)
				node_parent->left = Root;
			else
				node_parent->right = Root;
		}
		node->right = Root->left;
		Root->left = node;
		node->CheckHeight();
		Root->CheckHeight();
	}

	TEMP
		void AVLtree<T>::RotateLR(treeNode<T>* node, treeNode<T>* node_parent = NULL)
	{
		RotateRR(node->left,node);
		RotateLL(node,node_parent);
	}

	TEMP
		void AVLtree<T>::RotateRL(treeNode<T>* node, treeNode<T>* node_parent = NULL)
	{
		RotateLL(node->right,node);
		RotateRR(node,node_parent);
	}
	TEMP
		void AVLtree<T>::Maintain(stack<treeNode<T>*>&  road, T const& x)
	{
		treeNode<T>* temp=NULL;
		while(!road.isEmpty())
		{
			temp = road.pop();
			temp->CheckHeight();
			//if (!temp->checkheight())
				//break;
			if (differ(temp) == 2)
			{
				if (differ(temp->left) >= 0)
					RotateLL(temp, road.isEmpty() ? NULL : road.topData());
				else
					RotateLR(temp, road.isEmpty() ? NULL : road.topData());
				//break;
			}
			else if (differ(temp) == -2)
			{
				if (differ(temp->right) <= 0)
					RotateRR(temp, road.isEmpty() ? NULL : road.topData());
				else
					RotateRL(temp, road.isEmpty() ? NULL : road.topData());
				//break;
			}
		}
	}


	TEMP
		AVLtree<T>::AVLtree(T const a[] /* = NULL */, unsigned int n /* = 0 */)
	{
		re(i, n)
			insert(a[i]);
	}

	template<typename A, typename B>
	std::ostream& operator<<(std::ostream& out, const SearchNode<A, B>& other)
	{
		return out << "( " << other.index << " , " << other.data << " )";
	}

	template<typename A, typename B>
	SearchTree<A, B>::SearchTree(A const *Index /* = NULL */, B const * Data /* =NULL */, unsigned int n /* = 0 */)
	{
		re(i, n)
			insert(SearchNode<A, B>(Index[i], Data[i]));
	}

	template<typename A, typename B>
	SearchTree<A, B>::SearchTree(SearchTree<A, B> const *node, unsigned int n)
	{
		re(i, n)
			insert(node[i]);
	}

	template<typename A, typename B>
	treeNode<SearchNode<A, B>>*  SearchTree<A, B>::find(A const & index)const
	{
		SearchNode<A, B> temp(index, B());
		return AVLtree<SearchNode<A, B>>::find(temp);
	}
}