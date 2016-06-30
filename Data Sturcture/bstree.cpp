#include "bstree.h"
namespace ME{
	TEMP
		void bstree<T>::Maintain(stack<treeNode<T>*> & road, const T & x)
	{
		while(!road.isEmpty())
		{
			if (!road.pop()->checkheight())
				break;
		}
	}

	TEMP
		void bstree<T>::insert(T const &x)
	{
		treeNode<T>* target = root;
		stack<treeNode<T>*> road;
		if (target == NULL)
		{
			*(root = NodePool.pop())= treeNode<T>(x, 1);
			return;
		}
		while (1)
		{
			road.push(target);
			if (x < target->data)
			{
				if (target->left)target = target->left;
				else
				{
					*(target->left = NodePool.pop())=treeNode<T>(x, 1);
					break;
				}
			}
			else
			{
				if (target->right)target = target->right;
				else
				{

					*(target->right = NodePool.pop()) = treeNode<T>(x, 1);
					break;
				}
			}
		}
		Maintain(road, x);
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
			ans.Stack.push(P);
			if (x < P->data)
				P = P->left;
			else
				P = P->right;
		}
		return ans;
	}

	TEMP
		void bstree<T>::DelNode(T const &x)
	{
		treeNode<T>* temp=root,*P=NULL;
		stack <treeNode<T>*> road;
		queue<treeNode<T>*> second_road;
		while(temp)
		{
			if(temp->data==x)//找到了
			{
				//寻找恰好比他小的点。
				treeNode<T>* next = temp->left,*parent_next=temp;
				if (next != NULL)
				{
					if (next->right)//往右走了
					{
						while (next->right)
						{
							second_road.push(next);//记录下next下的路径。
							parent_next = next;
							next = next->right;
						}
						parent_next->right = next->left;
						next->left = temp->left;
					}
					road.push(next);//该节点替换了temp。放入路径进行调整。
					while (!second_road.isEmpty())
						road.push(second_road.pop());
					next->right = temp->right;
					if (P)
					{
						if (P->left == temp)
							P->left= next;
						else
							P->right = next;
					}
					else
					{
						root = next;
					}
				}
				else//没有往左走
				{
					if (P)
					{
						if (P->left == temp)
							P->left = temp->right;
						else
							P->right = temp->right;
					}
					else
					{
						root = temp->right;
					}
				}
				Maintain(road, x);
				NodePool.push(temp);
				break;
			}
			//查找部分。记录下路径。
			P = temp;
			road.push(temp);
			if (x < temp->data)
				temp = temp->left;
			else
				temp = temp->right;
		}
	}
}