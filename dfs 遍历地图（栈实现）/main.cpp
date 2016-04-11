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
using namespace std;
#define DEBUG
#undef re
#define re(i,n) for(unsigned int i=0;i<n;i++)

struct vector
{
	int y, x,i;//加了一个i用来辨识是那个方向下来的。
	vector(int y = 0, int x = 0, int i = 0) :x(x), y(y), i(i){}
	bool operator==(const vector& other)const{ return x == other.x&&y == other.y; }
	vector operator+(const vector & other)const{ return vector(y + other.y, x + other.x,i); }
	vector operator-(const vector & other)const{ return vector(y - other.y, x - other.x, i); }
	vector& operator+=(const vector & other){ x += other.x, y += other.y; return *this; }//这个效率更高
	vector& operator-=(const vector & other){ x -= other.x, y -= other.y; return *this; }
};
ostream& operator<<(ostream& out, const vector & other)
{
	return out << '(' << other.x << ',' << other.y << ')';
}
istream& operator>>(istream& in, vector & other)
{
	return in >> other.y >> other.x;
}
int map[20][20] = { 0 };
int visit[20][20] = { 0 };
int height = 0, width = 0;
const vector direction[8] =
{
	vector(1, 0), vector(-1, 0), vector(0, 1), vector(0, -1),
	vector(1, 1), vector(1, -1), vector(-1, 1), vector(-1, -1),
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

inline bool Judge(const vector &one)
{
	return	 0 <= one.y && 0 <= one.x&&one.y < height&&one.x < width
		&&map[one.y][one.x] == 0
		&& visit[one.y][one.x] == 0;
}

int Dfs(const vector &Begin,const vector &End)//模仿二叉树的前序遍历
{
	stack<vector> Stack;
	vector temp = Begin;
	int count = 0;
	while (Judge(temp) || !Stack.isEmpty())
	{
		while (Judge(temp)&&temp.i<8)
		{
			if (temp == End)
			{
				count++;
				//Output();
				//return 0;
			}
			Stack.push(temp);
			visit[temp.y][temp.x] = Stack.Top() + 1;//标记栈里面的。
			temp.i = 0;
			temp += direction[0];//一直往最左儿子遍历。
		}
		if(!Stack.isEmpty())
		{
			while (temp.i==8&&!Stack.isEmpty())//是否可以往右边走
			{
				temp = Stack.pop();//不可以，则返回上一层
				visit[temp.y][temp.x] = 0;//取消栈标记
			}
			(temp-=direction[temp.i])+=direction[temp.i + 1];//向右走
			temp.i++;//记录当前的方向。
		}
	}
	return count;
}
int Dfs(const vector &Begin,const vector &End,const vector &next,int my_time=0)//递归用引用效率高很多的。
{
	int ans = 0;
	if (!Judge(next) /*|| Count2>0*/)return 0;
	if (next == End)
	{
		//Output();
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
	vector Begin, End;
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