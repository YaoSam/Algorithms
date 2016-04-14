#pragma once
#include "SegmentTree.h"
#include <stdlib.h>
std::ostream& operator<<(std::ostream& out, const Segment& other)
{
	return out << "( " << other.left << " , " << other.right << " )";
}
std::istream& operator>>(std::istream& in, Segment &other)
{
	return in >> other.left >> other.right;
}
void SegmentTree::create(int a, int b,treeNode<Segment>* & node)
{
	node= new treeNode<Segment>(Segment(a, b));
	if (a+1<b)
	{
		create(a, (a + b) / 2, node->left);
		create((a + b) / 2, b, node->right);
	}
}
SegmentTree::SegmentTree(int a, int b) :NormalTree(Segment(a,b))//先用宽度优先吧……懒得想了。
{
	create(a, b, root);
}

void SegmentTree::insert(const Segment &x, treeNode<Segment>* node)
{
	if (node->data == x)
		(node->data).cover++;
	else if ((node->data).left + 1 == (node->data).right) return;
	else
	{
		int mid = ((node->data).left + (node->data).right) / 2;
		if (mid > x.right)
			insert(x, node->left);
		else if (mid < x.left)
			insert(x, node->right);
		else
		{
			insert(Segment(x.left, mid),node->left);
			insert(Segment(mid, x.right),node->right);
		}
	}
	return;
}

void SegmentTree::insert(const Segment &x)
{
	insert(x, root);
}

void SegmentTree::del(const Segment& x,treeNode<Segment>* node)
{
	if (node->data == x)
	{
		if ((node->data).cover>0)
			(node->data).cover--;
		else 
			return;
	}
	else if ((node->data).left + 1 == (node->data).right) return;
	else
	{
		int mid = ((node->data).left + (node->data).right) / 2;
		if (mid > x.right)
			del(x, node->left);
		else if (mid < x.left)
			del(x, node->right);
		else
		{
			del(Segment(x.left, mid),node->left);
			del(Segment(mid, x.right),node->right);
		}
	}
	return;
}

void SegmentTree::del(const Segment& x)
{
	del(x, root);
}
int SegmentTree::count(const treeNode<Segment>* node)const
{
	if (this == NULL)
		throw "count 出错……跳进了空指针";
	if ((node->Data()).cover>0)
		return (node->data).lenght();
	else if ((node->data).lenght() == 1)return 0;
	else
	{
		return count(node->left) + count(node->right);
	}
}
int SegmentTree::count()const
{
	return count(root);
}

//////////////////////////////////////////////////////////////////////////

Segment DiscreteSegTree::find(const Segment &origin)
{
	int a, b;
	treeNode<SearchNode<int,int>>* temp = tree.find(origin.left);
	if (temp == NULL)
		throw "非已有节点";
	a = (temp->Data()).data;
	temp = tree.find(origin.right);
	if (temp == NULL)
		throw "非已有节点";
	b = (temp->Data()).data;
	return Segment(a, b);
}

DiscreteSegTree::DiscreteSegTree(const Segment *Seg, const unsigned int n)
{
	int *num = new int[2*n];
	re(i, n)
	{
		num[2 * i] = Seg[i].left;
		num[2 * i + 1] = Seg[i].right;
	}
	Qsort(num, 0, 2 * n - 1);
	unsigned int Count=0;//记录不同的元素的个数
	re(i, 2 * n)//筛选出不同的元素
	{
		num[Count++] = num[i];
		int j = 1;
		while (i+j<2*n&&num[i] == num[i + j]) j++;//a[i]!=a[i+j]
		i += j - 1;
	}
	root = new treeNode<Segment>(Segment(0, Count));
	create(0, Count, root);
	Hash = new int[Count];
	re(i, Count)
	{
		tree.insert(SearchNode<int,int>(num[i], i));
		Hash[i] = num[i];
	}
	delete[] num;
	re(i, n)
		insert(Seg[i]);
}

DiscreteSegTree::DiscreteSegTree(const DiscreteSegTree& other) :SegmentTree(other)
{
	tree = other.tree;
	unsigned int Count = (root->Data()).right;
	Hash = new int[Count];
	memcpy(Hash, other.Hash, sizeof(int)*(Count));
}

DiscreteSegTree& DiscreteSegTree::operator=(const DiscreteSegTree& other)
{
	if (this == &other)return *this;
	delete[] Hash;
	unsigned int Count = (root->Data()).right;
	Hash = new int[Count];
	SegmentTree::operator=(other);
	tree = other.tree;
	memcpy(Hash, other.Hash, sizeof(int)*(Count));
	return *this;
}

void DiscreteSegTree::insert(const Segment &x)
{
	SegmentTree::insert(find(x));
}

void DiscreteSegTree::del(const Segment& x)
{
	SegmentTree::del(find(x));
}

int DiscreteSegTree::count(const treeNode< Segment>* node)const
{
	if (this == NULL)
		throw "count 出错……跳进了空指针";
	if ((node->Data()).cover > 0)
		return Hash[(node->Data()).right] - Hash[(node->Data()).left];
	else if ((node->Data()).lenght() == 1)return 0;
	else
	{
		return count(node->Left()) + count(node->Right());
	}
}
int DiscreteSegTree::count()const
{
	return count(root);
}