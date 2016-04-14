#include "btree.cpp"
TEMP
class FreeTree :public NormalTree <T>
{
public:
	FreeTree(T const & x) :
		NormalTree<T>(x,0)//这个0好像挺重要的。
	{}
	virtual ~FreeTree() {}
	virtual void insert(T const & x){ throw "未定义插入方法……Sorry"; }
	treeNode<T>* leftinsert(T const &x,treeNode<T>* y_node );
	treeNode<T>* rightinsert(T const &x, treeNode<T>* y_node);
};