#pragma once
#include <iostream>
#include "Stack.cpp"
#include "queue.cpp"
#include "normal.cpp"
#include <iterator>
#include <bitset>
#define re(i,n) for(unsigned int i=0;i<n;i++)
#undef NULL
#define NULL nullptr
namespace ME
{
	TEMP class NormalTree;
	TEMP class FreeTree;
	TEMP class bstree;
	TEMP class AVLtree;
	class SegmentTree;
	TEMP class HuffmanTree;
	TEMP
	class treeNode
	{
		friend class NormalTree < T > ;
		friend class FreeTree < T > ;
		friend class bstree < T > ;
		friend class AVLtree < T > ;
		friend class SegmentTree;
		friend class HuffmanTree < T > ;
	protected:
		T data;
		unsigned int height;
		treeNode<T>* left, *right;
		void CheckHeight()//更新高度
		{
			height = Max((left ? left->height : 0), (right ? right->height : 0)) + 1;
		}
		bool checkheight()
		{
			int Newheight = Max((left ? left->height : 0), (right ? right->height : 0)) + 1;
			if (height != Newheight)
			{
				height = Newheight;
				return 1;
			}
			return 0;
		}
		void Copy(treeNode<T>*& root, const treeNode<T>*  otherRoot);//模仿前序遍历实现的复制
		void Del(treeNode<T>*& root);//模仿后序遍历实现删除。
	public:
		treeNode<T>(T const &x = T(), 
			unsigned int h = 1,
			treeNode<T>* l = NULL,
			treeNode<T>* r = NULL) :
			data(x), height(h), left(l), right(r){}
		const T& Data()const{ return data; }
		treeNode<T>* Left()const{ return left; }
		treeNode<T>* Right()const{ return right; }
		unsigned int Height()const{ return height; }
	};
	TEMP
		class MemoryPool
	{
	protected:
		treeNode<T>* Pool;
		bool* flag;
		int pointer;
		unsigned size;
	public:
		MemoryPool(unsigned int MaxNumber=100000):
			Pool(new treeNode<T>[MaxNumber]),
			flag(new bool[MaxNumber]),
			pointer(0),
			size(MaxNumber)
		{
			memset(flag, 0, sizeof(bool)*size);
		}
		treeNode<T>* pop()
		{
			re(i,size)
			{
				if(flag[(pointer+i)%size]==0)
				{
					treeNode<T>* ans = Pool + (pointer + i) % size;
					flag[(pointer + i) % size] = true;
					pointer = (pointer + i + 1) % size;
					return ans;
				}
			}
			throw "Pool FULL!";
		}
		void push(treeNode<T>*& P) { flag[P - Pool] = 0; P = NULL; }
		~MemoryPool() { delete[]Pool, delete[] flag; }
	};

	TEMP
	class NormalTree//这东西用来继承吧！
	{
	protected:
		treeNode<T>* root;
		MemoryPool<T> static NodePool;
		void del(treeNode<T>* myRoot);
		void copy(treeNode<T>*& myRoot,const treeNode<T>* const& otherRoot);
		class m_iterator :public std::iterator < std::input_iterator_tag, T >
		{
		protected:
			const treeNode<T>* pCurrent, *m_root;
		public:
			m_iterator(treeNode<T>* P, treeNode<T>* R) :pCurrent(P), m_root(R){}
			virtual ~m_iterator(){}
			const T& operator*()const{return pCurrent->Data();}
			const T* operator->()const{return &(pCurrent->Data());}
			bool isEnd()const{ return pCurrent == NULL; }
			const treeNode<T>* operator()()const{ return pCurrent; }
			virtual void goFirst() = 0;
			bool operator==(const m_iterator& other)const { return pCurrent == other.pCurrent; }
		};
	public:
		class Pre_iterator :public m_iterator
		{
			stack<const treeNode<T>*> Stack;
			using m_iterator::pCurrent;
			using m_iterator::m_root;
		public:
			Pre_iterator() :m_iterator(nullptr, nullptr){};
			Pre_iterator(const NormalTree<T>& tree) :m_iterator(tree.Root(), tree.Root()){}
			void goFirst()override{ pCurrent = m_root; Stack.clear(); }
			Pre_iterator& operator++();
			static Pre_iterator end()//返回终点的迭代器。
			{
				return Pre_iterator(nullptr, nullptr);
			}
			bool operator==(const Pre_iterator& other)const { return pCurrent == other.pCurrent; }
		};
		class Mid_iterator :public m_iterator
		{
			stack<const treeNode<T>*> Stack;
			using m_iterator::pCurrent;
			using m_iterator::m_root;
			const treeNode<T>* begin_flag;
		public:
			Mid_iterator() :m_iterator(nullptr, nullptr),begin_flag(nullptr){};
			Mid_iterator(const NormalTree<T>& tree);
			void goFirst()override;
			bool isBegin()const { return pCurrent == begin_flag; }
			Mid_iterator& operator++();
			Mid_iterator& operator--();
			bool operator==(const Mid_iterator& other)const { return pCurrent == other.pCurrent; }
			TEMP friend class bstree;
		};
		class Post_iterator :public m_iterator
		{
			stack<const treeNode<T>*> Stack;
			using m_iterator::pCurrent;
			using m_iterator::m_root;
		public:
			Post_iterator() :m_iterator(nullptr, nullptr){};
			Post_iterator(const NormalTree<T>& tree);
			void goFirst()override;
			Post_iterator& operator++();
			bool operator==(const Post_iterator& other)const { return pCurrent == other.pCurrent; }
		};
		class Level_iterator :public m_iterator
		{
			queue<const treeNode<T>*> Queue;
			using m_iterator::pCurrent;
			using m_iterator::m_root;
		public:
			Level_iterator() :m_iterator(nullptr, nullptr){}
			Level_iterator(const NormalTree<T>& tree) :m_iterator(tree.Root(), tree.Root()){}
			void goFirst()override
			{
				pCurrent = m_root;
				Queue.clear();
			}
			Level_iterator& operator++();
			static Level_iterator end()
			{
				return Level_iterator(nullptr, nullptr);
			}
			bool operator==(const Level_iterator& other)const { return pCurrent == other.pCurrent; }
		};
		virtual treeNode<T>* find(T const & x)const;
		NormalTree(T const & x, unsigned int h = 1) :
			root(NodePool.pop()/*new treeNode<T>(x, h)*/)
		{
			*root = treeNode<T>(x, h);
		}
		NormalTree(treeNode<T>* r = NULL) :root(r){}
		NormalTree(NormalTree<T> const & other);
		NormalTree<T>& operator=(NormalTree<T> const & other);
		virtual ~NormalTree();
		unsigned int height(){ return root->height; }
		unsigned int NodeNum()const;
		void pre()const;
		void mid()const;
		void post()const;
		virtual void print()const;
		virtual Mid_iterator Find(T const & x)const;
		virtual void insert(T const & x) = 0;
		treeNode<T>* Root()const{ return root; }
		TEMP friend void swap(NormalTree<T>& a, NormalTree<T>& b);
	};
	TEMP MemoryPool<T> NormalTree<T>::NodePool;
	TEMP using Tree = NormalTree < T > ;
	TEMP using Pre = typename Tree<T>::Pre_iterator;
	TEMP using Mid = typename Tree<T>::Mid_iterator;
	TEMP using Post = typename Tree<T>::Post_iterator;
	TEMP using Level = typename Tree<T>::Level_iterator;
}