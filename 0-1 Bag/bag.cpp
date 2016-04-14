#include "bag.h"
bool operator==(object const & a, object const & b){
	return a.value == b.value&&a.weight == a.weight;
}
std::ostream &operator<<(std::ostream& out, object const & other)
{
	re(i, other.num)
		out
		<< "价值：" << other.value / (other.num) << " "
		<< "重量: " << other.weight / (other.num)
		//<< " 平均价值： " << other.value / other.weight
		<< std::endl;
	return out;
}
std::istream &operator>>(std::istream& in, object &other)
{
	return in >> other.value >> other.weight;
}

double BagState::CounRestValue()const
{
	if (RestNum < 0)
		return MyValue;
	double restValue = 0, room = RestRoom;
	unsigned int i = MyLocation->Height();//代表下一个物体
	re(j,RestNum-1)
	{
		if (room >= AllObject[i + j].weight)
		{
			//放入该物体;
			restValue += AllObject[i + j].value;
			room -= AllObject[i + j].weight;
		}
		else
			return restValue + AllObject[i].value / AllObject[i].weight;//没有考虑完。
	}
	return restValue;//此时已经考虑完了
}

BagState BagState::insert(bool flag)const
{
	BagState ans = *this;//上一个物体
	int i = 0;
	if (RestNum == 0)
		throw "已经考虑完了，无法插入。";
	if (RestRoom < 0)
		throw "空间为负。错误";
	if (flag)//要插入并且能插入
	{
		ans.MyLocation = SolutionTree->leftinsert(true, MyLocation);//height总是比物体下表多1
		i = MyLocation->Height();
		ans.MyValue += AllObject[i].value;
		ans.RestRoom -= AllObject[i].weight;
	}
	else
	{
		ans.MyLocation = SolutionTree->rightinsert(false, MyLocation);
	}
	ans.RestNum--;
	ans.MaxValue = MyValue + CounRestValue();
	return ans;
}

BagState::BagState(unsigned int Num, double limit,object things[])
	:RestNum(Num), AllObject(things), RestRoom(limit),//这三个变量感觉是一直要用的。
	MyValue(0)
{
	SolutionTree = new FreeTree<bool>(0);
	MyLocation=SolutionTree->Root();
	MaxValue = CounRestValue();
}

void BagState::keepSolution()
{
	treeNode<bool>* temp = MyLocation;
	unsigned int height=temp->Height();
	object *tempObject = new object[height];//这点内存就算了吧.我反正不释放了……╮(￣▽￣")╭
	RestNum = 0; 
	while (height > 0)
	{
		if (temp->Data())
			tempObject[RestNum++] = AllObject[height- 1];//一个从后往前。一个从前往后。
		temp = temp->Parent();
		height--;
	}
	SolutionTree->~FreeTree();
	SolutionTree = NULL;
	AllObject = tempObject;
}

std::ostream& operator<<(std::ostream& out, BagState const & other)
{
	if (other.SolutionTree != NULL)
	{
		treeNode<bool>* temp = other.MyLocation;
		while (temp->Height() > 0)//这里用parent也可以。
		{
			if (temp->Data())
				out << other.AllObject[temp->Height() - 1];
			temp = temp->Parent();
		}
	}
	else
	{
		re(i, other.RestNum)
			out << other.AllObject[i];
	}
	return out << std::endl;
}

BagState Solve(unsigned int n, double limit, object* thing)
{
	object *m_thing = new object[n + 1];
	memcpy(m_thing, thing, n*sizeof(object));
	Qsort_MaxToMin(m_thing, 0, n - 1);
	//下面压缩物体
	unsigned int i = 0, j = 0, k = 0, ObjectNum = 0,count=0;
	int delta = 0;
	while (j < n)
	{
		//查找相同物体,i记录起点，j记录终点
		for (i = j, j++; j < n; j++)
			if (m_thing[j]!=m_thing[i])
				break;
		//合并n个相同物体。
		for (k = 0, delta = j - i; (1 << k) <= delta; delta -= (1 << k), k++)//delta不断减少
			m_thing[ObjectNum++] = m_thing[i] * (1 << k);
		if (delta > 0)//如果还有剩下
			m_thing[ObjectNum++] = m_thing[i] * delta;
	}
	//solve
	BagState one(ObjectNum, limit, m_thing);
	MaxHeap<BagState> Heap_State;
	double CurrentMaxValue = 0;
	while (!one.isEnd())
	{
		count++;
		CurrentMaxValue = CurrentMaxValue < one.value() ? one.value() : CurrentMaxValue;
		if (one.restroom()>=m_thing[one.height()].weight)//容量越界不插入
			Heap_State.push(one.insert(true));
		Heap_State.push(one.insert(false));
		//取出最优节点
		one = Heap_State.pop();//因为弹出后得判断时候已经到了终点。
	}
	//std::cout << count << std::endl;
	one.keepSolution();
	delete[] m_thing;
	return one;
}