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
using namespace std;
#define DEBUG
#undef re
#define re(i,n) for(unsigned int i=0;i<n;i++)

struct vector
{
	int y, x;
	vector(int y=0, int x=0) :x(x), y(y){}
	bool operator==(const vector& other)const{ return x == other.x&&y == other.y; }
	vector operator+(const vector & other)const{ return vector(y + other.y, x + other.x); }
};
ostream& operator<<(ostream& out, const vector & other)
{
	return out << '(' << other.x << ',' << other.y << ')';
}
istream& operator>>(istream& in, vector & other)
{
	return in >> other.y >> other.x;
}
int map[1000][1000] = { 0 };
int visit[1000][1000] = { 0 };
int times = 0, height = 0, width = 0;
vector End,Begin;
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
	re(i,height)
	{
		re(j, width)
			cout << visit[i][j] << " ";
		cout << endl;
	}
	cout << endl;
}

bool Judge(vector one)
{
	return 0 <= one.y && 0 <= one.x&&one.y < height&&one.x < width
		&&visit[one.y][one.x]==0
		&&map[one.y][one.x]==0;
}
bool flag = 0;
void Dfs(vector next,int my_time=0)
{
	if (!Judge(next)||flag)return;
	//Output();
	if (next == End)
	{
		Output();
		//flag = 1;
		return;
	}
	re(i,8)
		{
			visit[next.y][next.x] = my_time+1;
			Dfs(next + direction[i],my_time+1);
			visit[next.y][next.x] = 0;
		}
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
	cin >> height >> width;
	cin >> Begin >> End;
	Input();
	Dfs(Begin);


	cout << "运行时间：" << (clock() - BeginTime) << endl;
#ifndef DEBUG
	system("pause");
#endif // !DEBUG
	return 0;
}