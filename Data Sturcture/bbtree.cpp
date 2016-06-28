#pragma once
#include "bbtree.h"
namespace ME{
	TEMP
		void AVLtree<T>::RotateLL(treeNode<T>* node)
	{
		treeNode<T>* Root = node->left;
		if (node->parent == NULL)//û�и��ڵ㡣��Root��Ϊ���ĸ���
		{
			root = Root;
			Root->parent = NULL;
		}
		else//�и��ڵ㣬���ڸ��׽ڵ�����ӡ�
		{
			if (node->parent->left == node)
				node->parent->leftlink(Root);
			else
				node->parent->rightlink(Root);
		}
		node->leftlink(Root->right);//�����ӽڵ������
		Root->rightlink(node);
		node->CheckHeight();
		Root->CheckHeight();
	}

	TEMP
		void AVLtree<T>::RotateRR(treeNode<T>* node)
	{
		treeNode<T>* Root = node->right, *P = node->parent;
		if (node->parent == NULL)
		{
			root = Root;
			Root->parent = NULL;
		}
		else 
		{
			if (node->parent->left == node)
				node->parent->leftlink(Root);
			else
				node->parent->rightlink(Root);
		}
		node->rightlink(Root->left);
		Root->leftlink(node);
		node->CheckHeight();
		Root->CheckHeight();
	}

	TEMP
		void AVLtree<T>::RotateLR(treeNode<T>* node)
	{
		RotateRR(node->left);
		RotateLL(node);
	}

	TEMP
		void AVLtree<T>::RotateRL(treeNode<T>* node)
	{
		RotateLL(node->right);
		RotateRR(node);
	}

	TEMP
		void AVLtree<T>::Maintain(treeNode<T>* node, T const &x)
	{
		while (node)//�������ϼ����С��ƽ��Ķ�������
		{
			node->CheckHeight();
			if (differ(node) == 2)
			{
				if (differ(node->left) >= 0)
					RotateLL(node);
				else
					RotateLR(node);
				//break;

			}
			else if (differ(node) == -2)
			{
				if (differ(node->right) <= 0)
					RotateRR(node);
				else
					RotateRL(node);
				//break;
			}
			else
				node = node->parent;
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