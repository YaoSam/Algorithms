#pragma  once
#include "btree.h"
namespace ME{
	TEMP void treeNode<T>::Del(treeNode<T>*& root)
	{
		stack<const treeNode<T>*> Stack;
		const treeNode<T>* temp = root, *temp2;
		if (root == NULL)return;
		while (temp != NULL)
		{
			while (temp != NULL)
			{
				Stack.push(temp);
				temp = temp->left;
			}
			temp = Stack.topData()->right;
		}
		temp = Stack.pop();
		while (temp != NULL)
		{
			temp2 = temp; delete temp2; //因为后面还要用到temp的信息。
			if (Stack.isEmpty())break;
			if (temp == Stack.topData()->left)
			{
				temp = Stack.topData()->right;
				while (temp != NULL)
				{
					while (temp != NULL)
					{
						Stack.push(temp);
						temp = temp->left;
					}
					temp = Stack.topData()->right;
				}
			}
			temp = Stack.pop();
		}
		root = NULL;
	}
	TEMP void treeNode<T>::Copy(treeNode<T>*& root, const treeNode<T>* otherRoot)
	{
		stack<const treeNode<T>*> Stack_other;
		const treeNode<T>* temp_other = otherRoot;
		stack<treeNode<T>*> Stack_this;
		treeNode<T> *temp_this = NULL;
		if (temp_other){
			temp_this = root = new treeNode<T>(temp_other->data, temp_other->height);
			Stack_other.push(temp_other);
			Stack_this.push(temp_this);
			temp_other = temp_other->left;
		}
		else root = NULL;
		while (temp_other != NULL || !Stack_other.isEmpty())
		{
			while (temp_other != NULL)//此时一定是向左走的。
			{
				temp_this->left = new treeNode<T>(temp_other->data, temp_other->height);
				temp_this = temp_this->left;//跟上temp_other的步伐
				Stack_this.push(temp_this);
				Stack_other.push(temp_other);
				temp_other = temp_other->left;
			}
			if (!Stack_other.isEmpty())//往回取一个点。向右走一步。
			{
				temp_other = Stack_other.pop()->right;
				temp_this = Stack_this.pop();
				if (temp_other)
				{
					temp_this->right = new treeNode<T>(temp_other->data, temp_other->height);
					temp_this = temp_this->right;
					Stack_other.push(temp_other);
					Stack_this.push(temp_this);
					temp_other = temp_other->left;//往左走。
				}
			}
		}
	}

	//////////////////////////////////////////////////////////////////////////
	TEMP void NormalTree<T>::del(treeNode<T>* myRoot)
	{
		if(myRoot)
		{
			del(myRoot->left);
			del(myRoot->right);
			NodePool.push(myRoot);
			//delete myRoot;
		}
	}

	TEMP void NormalTree<T>::copy(treeNode<T>*& myRoot, const treeNode<T>* const& otherRoot)
	{
		if(otherRoot)
		{
			*(myRoot = NodePool.pop())=treeNode<T>(otherRoot->data, otherRoot->height);
			//myRoot = new treeNode<T>(otherRoot->data, otherRoot->height);
			copy(myRoot->left, otherRoot->left);
			copy(myRoot->right, otherRoot->right);
		}
	}



	TEMP NormalTree<T>& NormalTree<T>::operator=(NormalTree<T> const & other)
	{
		if (this == &other)return *this;
		del(root);
		copy(root, other.root);
		return *this;
	}
	TEMP  NormalTree<T>::NormalTree(const NormalTree<T> & other):root(NULL)
	{
		copy(root, other.root);
	}
	TEMP NormalTree<T>::~NormalTree()
	{
		del(root);
	}

	TEMP unsigned int NormalTree<T>::NodeNum()const
	{
		unsigned int ans = 0;
		Pre<T> iter(*this);
		while(!iter.isEnd())
		{
			++iter;
			ans++;
		}
		return ans;
	}

	TEMP void NormalTree<T>::pre()const
	{
		stack<const treeNode<T>*> Stack;
		const treeNode<T>* temp = root;
		while (temp != NULL || !Stack.isEmpty())
		{
			while (temp != NULL)//不断向左遍历，并记录路径
			{
				std::cout << (temp->data) << " ";//关键：输出部分
				Stack.push(temp);
				temp = temp->left;
			}
			if (!Stack.isEmpty())//往回取一个点。向右走一步。
			{
				temp = Stack.pop()->right;
			}
		}
		std::cout << std::endl;
	}

	TEMP void NormalTree<T>::mid()const
	{
		stack<const treeNode<T>*> Stack;
		const treeNode<T>* temp = root;
		while (temp != NULL || !Stack.isEmpty())
		{
			while (temp != NULL)//不断向左走，到尽头了才输出
			{
				Stack.push(temp);
				temp = temp->left;
			}
			if (!Stack.isEmpty())//到了中间。输出。然后输出右边。
			{
				temp = Stack.pop();
				std::cout << (temp->data) << " ";
				temp = temp->right;
			}
		}
		std::cout << std::endl;
	}

	TEMP void NormalTree<T>::post()const
	{
		stack<const treeNode<T>*> Stack;
		const treeNode<T>* temp = root;
		if (root == NULL)return;
		while (temp != NULL)
		{
			while (temp != NULL)
			{
				Stack.push(temp);
				temp = temp->left;
			}
			temp = Stack.topData()->right;
		}
		temp = Stack.pop();
		while (temp != NULL)
		{
			std::cout << (temp->data) << " ";
			if (Stack.isEmpty())break;
			if (temp == Stack.topData()->left)
			{
				temp = Stack.topData()->right;
				while (temp != NULL)
				{
					while (temp != NULL)
					{
						Stack.push(temp);
						temp = temp->left;
					}
					temp = Stack.topData()->right;
				}
			}
			temp = Stack.pop();
		}
		std::cout << std::endl;
	}

	TEMP void NormalTree<T>::print()const
	{
		if (root == NULL)return;
		const treeNode<T>* temp;
		queue<const treeNode<T>*> Queue;
		Queue.push(root);
		while (!Queue.isEmpty())
		{
			temp = Queue.pop();
			if (temp->left)
				Queue.push(temp->left);
			if (temp->right)
				Queue.push(temp->right);
			std::cout << (temp->data) << " ";
		}
		std::cout << std::endl;
	}

	TEMP treeNode<T>* NormalTree<T>::find(T const & x)const
	{
		stack<treeNode<T>*> Stack;
		treeNode<T>* temp = root;
		while (temp != NULL || !Stack.isEmpty())
		{
			while (temp != NULL)//不断向左遍历，并记录路径
			{
				if (temp->data == x)
					return temp;
				Stack.push(temp);
				temp = temp->left;
			}
			if (!Stack.isEmpty())//往回取一个点。向右走一步。
			{
				temp = Stack.pop();
				temp = temp->right;
			}
		}
		return NULL;
	}

	TEMP
		Mid<T> NormalTree<T>::Find(T const& x) const
	{
		Mid<T> ans(*this);
		while (!ans.isEnd() && *ans != x)
			++ans;
		return ans;
	}

	//////////////////////////////////////////////////////////////////////////
	TEMP
		Pre<T>& NormalTree<T>::Pre_iterator::operator++()
	{
		Stack.push(pCurrent);
		pCurrent = pCurrent->Left();
		while (pCurrent == NULL&&!Stack.isEmpty())//能否回去
			pCurrent = Stack.pop()->Right();
		return *this;//可以向左走。退出，或者此时不能回去且P为空。结束。
	}

	TEMP
		void NormalTree<T>::Mid_iterator::goFirst()
	{
		pCurrent = m_root;
		Stack.clear();
		if (pCurrent == nullptr)return;;
		while (pCurrent->Left() != NULL)
		{
			Stack.push(pCurrent);
			pCurrent = pCurrent->Left();
		}
	}

	TEMP
		NormalTree<T>::Mid_iterator::Mid_iterator(const NormalTree<T>& tree) :m_iterator(tree.Root(), tree.Root())
	{
		goFirst();
		begin_flag = pCurrent;
	}

	TEMP
		Mid<T>& NormalTree<T>::Mid_iterator::operator++()
	{
		if (pCurrent->Right() != NULL)//最接近的书在下面
		{
			Stack.push(pCurrent);
			pCurrent = pCurrent->Right();
			while (pCurrent->Left() != NULL)//接着一直往左走
			{
				Stack.push(pCurrent);
				pCurrent = pCurrent->Left();
			}
			return *this;
		}
		while (!Stack.isEmpty())//否则，最接近的数载stack里。
		{
			if (pCurrent == Stack.topData()->Left())
			{
				pCurrent = Stack.pop();
				return *this;
			}
			pCurrent = Stack.pop();
		}
		pCurrent = nullptr;//到了尽头。
		return *this;
	}

	TEMP
		Mid<T>& NormalTree<T>::Mid_iterator:: operator--()
	{
		if (pCurrent->Left()!=NULL)
		{
			Stack.push(pCurrent);
			pCurrent = pCurrent->Left();
			while (pCurrent->Right()!=NULL)
			{
				Stack.push(pCurrent);
				pCurrent = pCurrent->Right();
			}
		}
		else while (!Stack.isEmpty())
		{
			if (pCurrent == Stack.topData()->Right())
			{
				pCurrent = Stack.pop();
				break;
			}
			pCurrent = Stack.pop();
		}
		return *this;
	}

	TEMP
		Level<T>& NormalTree<T>::Level_iterator::operator++()
	{
		if (pCurrent->Left())
			Queue.push(pCurrent->Left());
		if (pCurrent->Right())
			Queue.push(pCurrent->Right());
		if (!Queue.isEmpty())
			pCurrent = Queue.pop();
		else
			pCurrent = NULL;//否则置为空
		return *this;
	}

	TEMP
		void NormalTree<T>::Post_iterator::goFirst()
	{
		pCurrent = m_root;
		Stack.clear();
		while (pCurrent != NULL)
		{
			while (pCurrent != NULL)
			{
				Stack.push(pCurrent);
				pCurrent = pCurrent->Left();
			}
			pCurrent = Stack.topData()->Right();
		}
		if (Stack.isEmpty())//置为空
			pCurrent = NULL;
		else
			pCurrent = Stack.pop();
	}

	TEMP
		NormalTree<T>::Post_iterator::Post_iterator(const NormalTree<T>& tree) :m_iterator(tree.Root(), tree.Root())
	{
		goFirst();
	}

	TEMP
		Post<T>& NormalTree<T>::Post_iterator::operator++()//输出最左边的叶子节点。
	{
		if (Stack.isEmpty())//置为空
			pCurrent = NULL;
		else if (pCurrent == Stack.topData()->Left())
		{
			pCurrent = Stack.topData()->Right();//对其右边goFirst
			while (pCurrent != NULL)
			{
				while (pCurrent != NULL)
				{
					Stack.push(pCurrent);
					pCurrent = pCurrent->Left();
				}
				pCurrent = Stack.topData()->Right();
			}
			pCurrent = Stack.pop();
		}
		return *this;
	}
}