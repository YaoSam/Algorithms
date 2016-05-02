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
#include <string>
#include <time.h>
#include <algorithm>
using namespace std;
#undef re
#define re(i,n) for(unsigned int i=0;i<n;i++)
#define DEBUG

class box
{
	int map[4][4];
	box()
	{
		memset(map, 0, sizeof(map));
		write();
		write();
	}
	bool judge()const
	{
		return count_if(*map, *map + 16, [](auto a) {return a == 0; })==0;
	}
	void write()
	{
		auto number = (rand() % 2 + 1) * 2;										//2 or 4
		auto empty_number=count(*map, *map + 16, [](auto a){return a == 0; });	//计算0的数目
		empty_number = rand() % empty_number;								//随机取一个
		int *p = *map;
		re(i,4)
			re(j,4)
		{
			if(map[i][j]==0)
			{
				if (empty_number == 0)
				{
					map[i][j] == number;
					break;
				}
				empty_number--;
			}
		}
	}
	void right()
	{
		int Count=0;
		re(i,4)
		{
			re(j, 4)
			{
				if (map[i][Count] != 0)
					break;
				Count++;
			}
			if (Count > 0)
				memcmp(map[i], map[i] + Count, sizeof(int)*(4-Count));
			Count = 0;
		}
	}
	void left()
	{
		int Count = 3;
		re(i, 4)
		{
			re(j, 4)
			{
				if (map[i][Count] != 0)
					break;
				Count--;
			}
			if (Count<3)
				memcmp(map[i]+Count, map[i], sizeof(int)*(3 - Count));
			Count = 0;
		}
	}
};


int main()
{
	clock_t BeginTime = clock();
	srand(unsigned(time(NULL)));
#ifdef DEBUG
	FILE *input, *output; //没用的指针... ...
	freopen_s(&input, "in.txt", "r", stdin);
	freopen_s(&output, "out.txt", "w", stdout);
#endif
	try {
		/*主函数*/



	}
	catch (const char * error) { cout << error << endl; }
	cout << "运行时间：" << clock() - BeginTime << endl;
#ifndef DEBUG
	system("pause");
#endif // !DEBUG
	return 0;
}