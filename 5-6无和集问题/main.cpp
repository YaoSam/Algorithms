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
const int MAX_Num = 100;

struct Number_list//代表一个数字集合
{
	int Count;//放入数字的个数
	int number[MAX_Num];//记录放入的数字
	int Error_Number[MAX_Num*10];//记录已经被排除的数字
	Number_list() :
		Count(0)
	{
		memset(number, 0, sizeof(number));
		memset(number, 0, sizeof(Error_Number));
	}
	bool check(int const &n)const//判断数字是否能放入
	{
		return Error_Number[n]>0;
	}
	void push(int const &n)//放入数字。并且刷新一遍求和。
	{
		re(i,Count)
			Error_Number[number[i] + n]++;
		number[Count++] = n;
	}
	void pop()
	{
		int temp = number[Count - 1];//顶端数字
		re(i,Count-1)
			Error_Number[number[i] + temp]--;//清除由该数字造成的求和
		number[--Count] = 0;
	}
};

ostream& operator<<(ostream& out, const Number_list & other)
{
	re(i, other.Count)
		cout << other.number[i] << " ";
	return out;
}

Number_list list[10],ans[10];
int max_k = 0;
//只能到58了……艹………
void dfs(int n,int k=1)
{
	re(i,n)//遍历n个集合
		if (list[i].check(k) == 0)//能否放入。
		{
			list[i].push(k);
			if (k > max_k)//成功在n个表里面放入k个数。新的最优解。记录。
			{
				max_k = k;
				re(j, n)ans[j] = list[j];
			}
			dfs(n, k + 1);//放入下一个数
			list[i].pop();//清除标记
		}
}

int main()
{
	clock_t BeginTime = clock();
	srand(unsigned(time(NULL)));
#ifdef DEBUG
	FILE *input, *output; //没用的指针... ...
	freopen_s(&input, "in.txt", "r", stdin);
	freopen_s(&output, "out.txt", "w", stdout);
#endif

	/*主函数体*/
	int n = 3;
	dfs(n);
	cout<< max_k<< endl;
	re(i, n)
		cout << ans[i] << endl;

#ifndef DEBUG
	system("pause");
#endif // !DEBUG
	return 0;
}