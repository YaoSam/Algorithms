#include "btree.cpp"
TEMP
class FreeTree :public Tree <T>::m_iterator
{
public:
	FreeTree(T const & x) :
		Tree<T>(x,0)//这个0好像挺重要的。
	{}
	virtual ~FreeTree() {}
	virtual void insert(T const & x){ throw "未定义插入方法……Sorry"; }
	treeNode<T>* leftinsert(T const &x,treeNode<T>* y_node );
	treeNode<T>* rightinsert(T const &x, treeNode<T>* y_node);
};