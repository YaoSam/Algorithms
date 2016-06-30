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
			temp2 = temp; delete temp2; //��Ϊ���滹Ҫ�õ�temp����Ϣ��
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
			while (temp_other != NULL)//��ʱһ���������ߵġ�
			{
				temp_this->left = new treeNode<T>(temp_other->data, temp_other->height);
				temp_this = temp_this->left;//����temp_other�Ĳ���
				Stack_this.push(temp_this);
				Stack_other.push(temp_other);
				temp_other = temp_other->left;
			}
			if (!Stack_other.isEmpty())//����ȡһ���㡣������һ����
			{
				temp_other = Stack_other.pop()->right;
				temp_this = Stack_this.pop();
				if (temp_other)
				{
					temp_this->right = new treeNode<T>(temp_other->data, temp_other->height);
					temp_this = temp_this->right;
					Stack_other.push(temp_other);
					Stack_this.push(temp_this);
					temp_other = temp_other->left;//�����ߡ�
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
			while (temp != NULL)//�����������������¼·��
			{
				std::cout << (temp->data) << " ";//�ؼ����������
				Stack.push(temp);
				temp = temp->left;
			}
			if (!Stack.isEmpty())//����ȡһ���㡣������һ����
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
			while (temp != NULL)//���������ߣ�����ͷ�˲����
			{
				Stack.push(temp);
				temp = temp->left;
			}
			if (!Stack.isEmpty())//�����м䡣�����Ȼ������ұߡ�
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
			while (temp != NULL)//�����������������¼·��
			{
				if (temp->data == x)
					return temp;
				Stack.push(temp);
				temp = temp->left;
			}
			if (!Stack.isEmpty())//����ȡһ���㡣������һ����
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
		while (pCurrent == NULL&&!Stack.isEmpty())//�ܷ��ȥ
			pCurrent = Stack.pop()->Right();
		return *this;//���������ߡ��˳������ߴ�ʱ���ܻ�ȥ��PΪ�ա�������
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
		if (pCurrent->Right() != NULL)//��ӽ�����������
		{
			Stack.push(pCurrent);
			pCurrent = pCurrent->Right();
			while (pCurrent->Left() != NULL)//����һֱ������
			{
				Stack.push(pCurrent);
				pCurrent = pCurrent->Left();
			}
			return *this;
		}
		while (!Stack.isEmpty())//������ӽ�������stack�
		{
			if (pCurrent == Stack.topData()->Left())
			{
				pCurrent = Stack.pop();
				return *this;
			}
			pCurrent = Stack.pop();
		}
		pCurrent = nullptr;//���˾�ͷ��
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
			pCurrent = NULL;//������Ϊ��
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
		if (Stack.isEmpty())//��Ϊ��
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
		Post<T>& NormalTree<T>::Post_iterator::operator++()//�������ߵ�Ҷ�ӽڵ㡣
	{
		if (Stack.isEmpty())//��Ϊ��
			pCurrent = NULL;
		else if (pCurrent == Stack.topData()->Left())
		{
			pCurrent = Stack.topData()->Right();//�����ұ�goFirst
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