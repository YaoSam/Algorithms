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
#include <bitset>
#include <time.h>
using namespace std;
#define DEBUG
#undef re
#define re(i,n) for(unsigned int i=0;i<n;i++)

const int MaxNode = 100;
int map[MaxNode][MaxNode] = { 0 };
int road[1000] = { 0 };
int visit[MaxNode] = { 0 };
int Reached_Node = 0;
int node_number,edge_number;
int min_cost=0;
void dfs(int from,int current_cost,int level=0)
{
	if (Reached_Node == node_number/*&&from==0*/)//是否要求回路
	{
		/*更新最优值*/
		min_cost = current_cost;
		/*输出解*/
		cout << min_cost << endl;
		re(i, level)
			cout << road[i];
		cout << endl;
		cout << map[0][road[0]-1] << " ";
		re(i, level - 1)
			cout << map[road[i]-1][road[i + 1]-1] << " ";
		cout << endl;
		return;
	}
	re(i, node_number)
		if (map[from][i]>0&&current_cost+map[from][i]<min_cost)
		{
			if (visit[i] == 0)Reached_Node++;
			visit[i]++;//由于可能会有重复走的情况。所以标记必须多重。
			road[level]=i+1;//记录路径。
			dfs(i, current_cost + map[from][i],level+1);
			visit[i]--;
			if (visit[i] == 0)Reached_Node--;
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
	cin >>node_number>> edge_number;
	memset(road, 0, sizeof(road));
	memset(map, 0, sizeof(map));
	int from, to;
	int cost;
	re(i,edge_number)
	{
		cin>>from>>to>>cost;
		min_cost += cost;
		map[from-1][to-1] = cost;
	}
	re(i,node_number)//假如不要求回路。则起点并不是对称的。所以每个点都得遍历一遍。
		dfs(i, 0);
	//dfs(0,0);
	cout << "运行时间：" << (clock() - BeginTime) << endl;
#ifndef DEBUG
	system("pause");
#endif // !DEBUG
	return 0;
}