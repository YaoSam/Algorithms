#pragma once
#include "..\Data Sturcture\ALL.h"
struct Segment
{
	int left, right, cover;
	Segment(int L=0, int R=0, int C=0) :left(L), right(R), cover(C){}
	int lenght()const { return right - left; }
	bool operator>(const Segment& b)const{ return left + right > b.left + b.right; }
	bool operator==(const Segment& b)const { return left == b.left&&right == b.right; }//虽然说上面那个应该够用了。以防万一。
	friend std::ostream& operator<<(std::ostream& out, const Segment& other);
	friend std::istream& operator>>(std::istream& in, Segment &other);
};

class SegmentTree:public NormalTree<Segment>
{
protected:
	//基本用递归实现。
	virtual void create(int a, int b, treeNode<Segment>* &node);
	virtual void insert(const Segment &x, treeNode<Segment>* node);
	virtual void del(const Segment& x, treeNode<Segment>* node);
	virtual int count(const treeNode<Segment>* node)const;
public:
	SegmentTree(){}
	SegmentTree(int a, int b);
	virtual ~SegmentTree(){}
	virtual void insert(int a, int b){ insert(Segment(a, b)); }
	virtual void insert(const Segment &x);
	virtual void del(const Segment& x);
	virtual int count()const;
};


class DiscreteSegTree :public SegmentTree
{
	SearchTree<int,int> tree;
	int *Hash;
	Segment find(const Segment &origin);
	int count(const treeNode< Segment>* node)const;
public:
	DiscreteSegTree(const Segment *Seg, const unsigned int n);
	DiscreteSegTree(const DiscreteSegTree& other);//既然用了动态分配。那就顺便搞定这里吧。
	DiscreteSegTree& operator=(const DiscreteSegTree& other);
	void insert(const Segment &x);
	void del(const Segment& x);
	int count()const;
	~DiscreteSegTree(){ delete[] Hash; }
};