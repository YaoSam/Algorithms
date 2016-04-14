#pragma once
#include "iterator.h"

TEMP
T m_iterator<T>::operator*()const
{
	if (pCurrent == NULL)
		throw "iterator range error\n";
	else
		return pCurrent->Data();
}

TEMP
treeNode<T>* Pre_iterator<T>::operator++()
{
	if (pCurrent == NULL)	throw "Pre_iterator range error\n";
	Stack.push(pCurrent);
	pCurrent = pCurrent->Left();
	while (pCurrent == NULL&&!Stack.isEmpty())//能否回去
	{
		pCurrent = Stack.pop();
		pCurrent = pCurrent->Right();
		if (pCurrent)
			break;
	}
	return pCurrent;//可以向左走。退出，或者此时不能回去且P为空。结束。
}

TEMP
void Mid_iterator<T>::goFirst()
{
	pCurrent = m_root;
	Stack.clear();
	while (pCurrent != NULL)
	{
		Stack.push(pCurrent);
		pCurrent = pCurrent->Left();
	}
	pCurrent = Stack.topData();
	return;
}

TEMP
Mid_iterator<T>::Mid_iterator(NormalTree<T>* tree) :m_iterator<T>(tree->Root(),tree->Root())
{
	goFirst();
}

TEMP 
treeNode<T>* Mid_iterator<T>::operator++()
{
	if (Stack.isEmpty())
		throw "Mid_iterator range error\n";
	pCurrent=Stack.pop();//这个已经被输出了。说明这个的左边已经不用管了。
	if (pCurrent->Right()!= NULL)
	{
		treeNode<T>* temp = pCurrent->Right();//往右边走一步
		while (temp != NULL)//接着一直往右走
		{
			Stack.push(temp);
			temp = temp->Left();
		}
	}
	if (Stack.isEmpty())
		pCurrent = NULL;
	else
		pCurrent = Stack.topData();
	return pCurrent;
}

TEMP
treeNode<T>* Level_iterator<T>::operator++()
{
	if (pCurrent->Left())
		Queue.push(pCurrent->Left());
	if (pCurrent->Right())
		Queue.push(pCurrent->Right());
	if (!Queue.isEmpty())
		pCurrent = Queue.pop();
	else
		pCurrent = NULL;//否则置为空
	return pCurrent;
}

TEMP 
void Post_iterator<T>::goFirst()
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
Post_iterator<T>::Post_iterator(NormalTree<T>* tree) :m_iterator(tree->Root(),tree->Root())
{
	goFirst();
}

TEMP
treeNode<T>* Post_iterator<T>::operator++()//输出最左边的叶子节点。
{
	if (pCurrent==NULL)
		throw "Post_iterator range error\n";
	if (Stack.isEmpty())//置为空
		return pCurrent = NULL;
	if (pCurrent == Stack.topData()->Left())
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
	}
	pCurrent = Stack.pop();
	return pCurrent;
}