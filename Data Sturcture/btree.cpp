#pragma  once
#include "btree.h"
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
	treeNode<T> *temp_this=NULL;
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
			temp_this->left = new treeNode<T>(temp_other->data, temp_other->height, temp_this);
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
				temp_this->right = new treeNode<T>(temp_other->data, temp_other->height, temp_this);
				temp_this = temp_this->right;
				Stack_other.push(temp_other);
				Stack_this.push(temp_this);
				temp_other = temp_other->left;//往左走。
			}
		}
	}
}

TEMP void treeNode<T>::leftlink(treeNode<T>* other)
{
	left = other;
	if (other)
		other->parent = this;
}

TEMP void treeNode<T>::rightlink(treeNode<T>* other)
{
	right = other;
	if (other)
		other->parent = this;
}

//////////////////////////////////////////////////////////////////////////

TEMP NormalTree<T>& NormalTree<T>::operator=(NormalTree<T> const & other)
{
	if (this == &other)return *this;
	root->Del(root);
	root->Copy(root, other.root);
	return *this;
}
TEMP  NormalTree<T>::NormalTree(const NormalTree<T> & other)
{
	root->Copy(root, other.root);
}
TEMP NormalTree<T>::~NormalTree()
{
	root->Del(root);
}

TEMP unsigned int NormalTree<T>::NodeNum()const
{
	stack<const treeNode<T>*> Stack;
	const treeNode<T>* temp = root;
	unsigned int ans=0;
	while (temp != NULL || !Stack.isEmpty())
	{
		while (temp != NULL)
		{
			ans++;//输出部分
			Stack.push(temp);
			temp = temp->left;
		}
		if (!Stack.isEmpty())
		{
			temp = Stack.pop();
			temp = temp->right;
		}
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
		if(temp == Stack.topData()->left)
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
	if (root==NULL)return;
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

TEMP void Swap(NormalTree<T>* a, NormalTree<T>* b)
{
	Swap(a->root,b->root);
}