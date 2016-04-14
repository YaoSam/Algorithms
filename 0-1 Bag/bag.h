#include "..\Data Sturcture\heap.cpp"
#include "..\Data Sturcture\freetree.cpp"

struct object
{
	unsigned int num;//记录融合了多少个物体
	double weight, value;
	object(double value = 0, double weight = 0, unsigned int num = 1) :
		value(value), weight(weight), num(num){}
	bool operator>(object const & other)const{//用价值密度作为标准
		if (value*other.weight == other.value*weight)return value > other.value;//用来压缩背包用的。
		return value*other.weight > other.value*weight;
	}
	object operator*(unsigned int n){
		return object(value*n, weight*n, num*n);
	}
};
bool operator==(object const & a, object const & b);
//输出格式： 价值：? 重量: ? *数目
std::ostream &operator<<(std::ostream& out, object const & other);
//输入格式：vlaue weight
std::istream &operator>>(std::istream& in, object &other);

class BagState
{
	double MaxValue, MyValue, RestRoom;
	unsigned int RestNum;
	treeNode<bool>* MyLocation;
	//一下的要慎重delete
	FreeTree<bool>* SolutionTree;
	object* AllObject;
	//计算剩余价值
	double CounRestValue()const;
public:
	//优化内存。
	void keepSolution();
	void clear(){ if (AllObject)delete[]AllObject; }
	BagState(){}
	BagState(unsigned int thingNum, double limit,object things[]);
	//返回当前背包价值
	double value()const{ return MyValue; }
	//用来判断是否已经装满
	double restroom()const{ return RestRoom; }
	//用来判断是否到了底层
	bool isEnd()const{ return RestNum ==0; }
	//其实isEnd()可以用这个代替……
	unsigned int height()const { return MyLocation->Height(); }
	//遍历物体。生成新的背包。flag=1则放入。flag=0则略过。
	BagState insert(bool flag)const;
	//代表其在优先队列的优先级，用来存入堆，判别标准：其价值上界(MaxValue)
	bool operator>(BagState const & other)const
	{
		return MaxValue > other.MaxValue;
	}
	//输出背包状态
	friend std::ostream& operator<<(std::ostream& out, BagState const & other);
};


//关键。就是通过该接口来解决背包问题。
BagState Solve(unsigned int n, double limit, object* thing);