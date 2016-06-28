#include "bstree.h"
namespace ME{
	TEMP
		void bstree<T>::Maintain(treeNode<T>* other, T const& x)
	{
		while (other){
			other->CheckHeight();
			other = other->parent;
		}
	}
	TEMP
		void bstree<T>::insert(T const &x)
	{
		treeNode<T>* target = root;
		if (target == NULL)
		{
			//root = new treeNode<T>(x, 1);
			*(root = NodePool.pop())= treeNode<T>(x, 1);
			return;
		}
		while (1)
		{
			if (x < target->data)
			{
				if (target->left)target = target->left;
				else
				{
					*(target->left = NodePool.pop())=treeNode<T>(x, 1, target);
					//target->left = new treeNode<T>(x, 1, target);
					break;
				}
			}
			else
			{
				if (target->right)target = target->right;
				else
				{

					*(target->right = NodePool.pop()) = treeNode<T>(x, 1, target);
					//target->right = new treeNode<T>(x, 1, target);
					break;
				}
			}
		}
		Maintain(target, x);
	}

	TEMP
		bstree<T>::bstree(T const a[] /* = NULL */, unsigned int n /* = 0 */)
	{
		re(i, n)
			insert(a[i]);
	}
	TEMP
		treeNode<T>* bstree<T>::FindLeftNext(const treeNode<T>* a)const
	{
		if (a == NULL)
			return NULL;
		treeNode<T>* temp = a->left;
		if (temp != NULL)
		{
			while (temp->right != NULL)
				temp = temp->right;
		}
		return temp;
	}
	TEMP
		treeNode<T>* bstree<T>::FindRightNext(const treeNode<T>* a)const
	{
		if (a == NULL)
			return NULL;
		treeNode<T>* temp = a->right;
		if (temp != NULL)
		{
			while (temp->left != NULL)
				temp = temp->left;
		}
		return temp;
	}

	TEMP
		treeNode<T>* bstree<T>::find(T const &x)const
	{
		treeNode<T>* temp = root;
		while (temp)
		{
			if (temp->data == x)
				return temp;
			if (x < temp->data)
				temp = temp->left;
			else
				temp = temp->right;
		}
		return NULL;
	}

	TEMP
		Mid<T> bstree<T>::Find(const T& x) const
	{
		Mid<T> ans;
		ans.NormalTree::m_iterator::m_root = root;
		ans.NormalTree::m_iterator::pCurrent = root;
		const  treeNode<T>* P = ans.NormalTree::m_iterator::pCurrent;
		while(P)
		{
			if (P->data == x)
			{
				ans.NormalTree::m_iterator::pCurrent = P;
				break;
			}
			if (x < P->data)
				P = P->left;
			else
				P = P->right;
			ans.Stack.push(P->parent);
		}
		return ans;
	}

	TEMP
		void bstree<T>::DelNode(T const &x)
	{
		treeNode<T>* target = find(x);
		if (target == NULL) return;
		treeNode<T>* Next = FindLeftNext(target), *P;
		if (Next != NULL)
		{
			P = Next->parent;
			Swap(Next->data, target->data);
			if (P == target)
				P->leftlink(Next->left);
			else
				P->rightlink(Next->left);
			NodePool.push(Next);
			//delete Next;
			Maintain(P, x);
		}
		else
		{
			Next = FindRightNext(target);
			if (Next != NULL)
			{
				P = Next->parent;
				Swap(Next->data, target->data);
				if (P == target)
					P->rightlink(Next->right);
				else
					P->leftlink(Next->right);
				NodePool.push(Next);
				//delete Next;
				Maintain(P, x);
			}
			else//P就是叶子节点
			{
				P = target->parent;
				if (P)
				{
					if (P->left == target)
						P->left = NULL;
					else
						P->right = NULL;
					Maintain(P, x);//其实maintain和delete的位置随意。在调整了P之后就可以了。
				}
				else
					root = NULL;
				NodePool.push(target);
				//delete target;
			}
		}
	}
}