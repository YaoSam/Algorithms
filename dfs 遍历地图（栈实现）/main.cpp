/*
*　　　　　　　　┏┓　　　┏┓+ +
*　　　　　　　┏┛┻━━━┛┻┓ + +
*　　　　　　　┃　　　　　　　┃ 　
*　　　　　　　┃　　　━　　　┃ ++ + + +
*　　　　　　 ████━████ ┃+
*　　　　　　　┃　　　　　　　┃ +
*　　　　　　　┃　　　┻　　　┃
*　　　　　　　┃　　　　　　　┃ + +
*　　　　　　　┗━┓　　　┏━┛
*　　　　　　　　　┃　　　┃　　　　　　　　　　　
*　　　　　　　　　┃　　　┃ + + + +
*　　　　　　　　　┃　　　┃　　　　Code is far away from bug with the animal protecting　　　　　　　
*　　　　　　　　　┃　　　┃ + 　　　　神兽保佑,代码无bug　　
*　　　　　　　　　┃　　　┃
*　　　　　　　　　┃　　　┃　　+　　　　　　　　　
*　　　　　　　　　┃　 　　┗━━━┓ + +
*　　　　　　　　　┃ 　　　　　　　┣┓
*　　　　　　　　　┃ 　　　　　　　┏┛
*　　　　　　　　　┗┓┓┏━┳┓┏┛ + + + +
*　　　　　　　　　　┃┫┫　┃┫┫
*　　　　　　　　　　┗┻┛　┗┻┛+ + + +
*/
#include <iostream>
#include <time.h>
#include "C:\Users\Sam\Documents\C++\数据结构汇总\Data Structure\Data Sturcture\Stack.cpp"
#include "C:\Users\Sam\Documents\C++\数据结构汇总\Data Structure\Data Sturcture\ALL.h"
using namespace std;
#define DEBUG
#undef re
#define re(i,n) for(unsigned int i=0;i<n;i++)

struct Vector
{
	int y, x,i;//加了一个i用来辨识是那个方向下来的。
	Vector(int y = 0, int x = 0, int i = 0) :x(x), y(y), i(i){}
	bool operator==(const Vector& other)const{ return x == other.x&&y == other.y; }
	Vector operator+(const Vector & other)const{ return Vector(y + other.y, x + other.x,i); }
	Vector operator-(const Vector & other)const{ return Vector(y - other.y, x - other.x, i); }
	Vector& operator+=(const Vector & other){ x += other.x, y += other.y; return *this; }//这个效率更高
	Vector& operator-=(const Vector & other){ x -= other.x, y -= other.y; return *this; }
};
ostream& operator<<(ostream& out, const Vector & other)
{
	return out << '(' << other.x << ',' << other.y << ')';
}
istream& operator>>(istream& in, Vector & other)
{
	return in >> other.y >> other.x;
}
int map[20][20] = { 0 };
int visit[20][20] = { 0 };
unsigned int height = 0, width = 0;
const Vector direction[8] =
{
	Vector(1, 0), Vector(-1, 0), Vector(0, 1), Vector(0, -1),
	Vector(1, 1), Vector(1, -1), Vector(-1, 1), Vector(-1, -1),
};
void Input()
{
	re(i, height)
		re(j, width)
		cin >> map[i][j];
}

void Output()
{
	re(i, height)
	{
		re(j, width)
		{
			if (visit[i][j] < 10)
				cout << ' ';
			cout << visit[i][j] << ' ';
		}
		cout << endl;
	}
	cout << endl;
}

bool Judge(const Vector &one)
{
	return 0 <= one.y && 0 <= one.x&&one.y < height&&one.x < width&&map[one.y][one.x] == 0 && visit[one.y][one.x] == 0;
}

int Dfs(const Vector &Begin,const Vector &End)//模仿二叉树的前序遍历
{
	stack<Vector> Stack,solution;
	int count = 0;
	Vector temp = Begin;
	const int direction_number = 8;
	while (Judge(temp) || !Stack.isEmpty())
	{
		while (Judge(temp)&&temp.i<direction_number)
		{
			if (temp == End)
			{
				if (solution.isEmpty() || solution.Top() > Stack.Top())
				{
					count++;
					solution = Stack;
					cout << solution;
					Output();
				}
			}
			Stack.push(temp);
			visit[temp.y][temp.x] = Stack.Top() + 1;//标记栈里面的。
			temp.i = 0;
			temp += direction[0];//一直往最左儿子遍历。
		}
		if(!Stack.isEmpty())
		{
			while (((!solution.isEmpty() && solution.Top() <= Stack.Top()) //最优条件筛选
				||temp.i == direction_number-1) && !Stack.isEmpty())//是否可以往右边走
			{
				temp = Stack.pop();//不可以，则返回上一层
				visit[temp.y][temp.x] = 0;//取消栈标记
			}
			cout << temp.i << endl;
			(temp-=direction[temp.i])+=direction[temp.i + 1];//向右走
			temp.i++;//记录当前的方向。
			cout << temp << endl;

		}
	}
	return count;
}

int times = 0;
int Dfs(const Vector &Begin,const Vector &End,const Vector &next,int my_time=0)//递归用引用效率高很多的。
{
	if ((times > 0 && my_time >= times)||!Judge(next))return 0;
	int ans = 0;
	if (next == End)
	{
		Output();
		times = my_time;
		return 1;
	}
	re(i, 8)
	{
		visit[next.y][next.x] = my_time + 1;
		 ans+=Dfs(Begin,End,next + direction[i], my_time + 1);
		visit[next.y][next.x] = 0;
	}
	return ans;
}


int main()
{
	clock_t BeginTime = clock();
	srand(unsigned(time(nullptr)));
#ifdef DEBUG
	FILE *input, *output; //没用的指针... ...
	freopen_s(&input, "in.txt", "r", stdin);
	freopen_s(&output, "out.txt", "w", stdout);
#endif

	/*主函数体*/
	Vector Begin, End;
	cin >> height >> width;
	cin >> Begin >> End;
	Input();
	clock_t time1 = clock();
	cout<<Dfs(Begin, End)<<endl;
	cout <<"运行时间: "<< clock() - time1 << endl;

	memset(visit, 0, sizeof(visit));

	time1 = clock();
	cout << Dfs(Begin, End, Begin)<<endl;
	cout << "运行时间: " << clock() - time1 << endl;

	cout << "运行时间：" << (clock() - BeginTime) << endl;
#ifndef DEBUG
	system("pause");
#endif // !DEBUG
	return 0;
}