#include "btree.cpp"
TEMP
class FreeTree :public Tree <T>::m_iterator
{
public:
	FreeTree(T const & x) :
		Tree<T>(x,0)//���0����ͦ��Ҫ�ġ�
	{}
	virtual ~FreeTree() {}
	virtual void insert(T const & x){ throw "δ������뷽������Sorry"; }
	treeNode<T>* leftinsert(T const &x,treeNode<T>* y_node );
	treeNode<T>* rightinsert(T const &x, treeNode<T>* y_node);
};