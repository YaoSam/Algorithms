//#pragma once
//#include "btree.cpp"
//
//TEMP
//class m_iterator
//{
//protected:
//	treeNode<T>* pCurrent, *m_root;
//public:
//	m_iterator(treeNode<T>* P, treeNode<T>* R) :pCurrent(P), m_root(R){}
//	virtual ~m_iterator(){}
//	inline T operator*()const;
//	bool isEnd()const{ return pCurrent == NULL; }
//	 treeNode<T>* operator()()const{ return pCurrent; }
//	virtual void goFirst()=0;
//	virtual treeNode<T>* operator++()=0;
//};
//
//TEMP
//class Pre_iterator :public m_iterator < T >
//{
//	stack<treeNode<T>*> Stack;
//	using m_iterator<T>::pCurrent;
//	using m_iterator<T>::m_root;
//public:
//	Pre_iterator(NormalTree<T> *tree) :m_iterator(tree->Root(), tree->Root()){}
//	void goFirst()override{ pCurrent = m_root; Stack.clear(); }
//	treeNode<T>* operator++()override;
//};
//
//TEMP 
//class Mid_iterator :public m_iterator < T >
//{
//	stack<treeNode<T>*> Stack;
//	using m_iterator<T>::pCurrent;
//	using m_iterator<T>::m_root;
//public:
//	Mid_iterator(NormalTree<T>* tree);
//	void goFirst()override;
//	treeNode<T>* operator++()override;
//};
//
//TEMP
//class Post_iterator :public m_iterator < T >
//{
//	stack<treeNode<T>*> Stack;
//	using m_iterator<T>::pCurrent;
//	using m_iterator<T>::m_root;
//public:
//	Post_iterator(NormalTree<T>* tree);
//	void goFirst()override;
//	treeNode<T>* operator++()override;
//};
//
//TEMP 
//class Level_iterator :public m_iterator < T >
//{
//	queue<treeNode<T>*> Queue;
//	using m_iterator<T>::pCurrent;
//	using m_iterator<T>::m_root;
//public:
//	Level_iterator(NormalTree<T>* tree) :m_iterator(tree->Root(), tree->Root()){}
//	void goFirst()override
//	{
//		pCurrent = m_root;
//		Queue.clear(); 
//	}
//	treeNode<T>* operator++()override;
//};