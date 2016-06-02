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
#include <vector>
using namespace std;
#undef re
#define re(i,n) for(unsigned int i=0;i<n;i++)
#define DEBUG

class matrix
{
	int row, col,product_num;
public:
	matrix(int R=0,int C=0,int num=0):row(R),col(C),product_num(num){}
	matrix operator*(const matrix& other)const
	{
		if (col != other.row)throw"行列数目不同，不能相乘";
		return matrix(row,other.col,*this+other);
	}
	bool operator>(const matrix& other)const
	{
		return product_num > other.product_num;
	}
	int operator+(const matrix& other)const
	{
		return product_num + other.product_num + col*row*other.col;
	}
	int count()const { return product_num; }
	friend ostream& operator<<(ostream& out, const matrix& other)
	{
		return out << "(" << other.row << "," << other.col << "," << other.product_num << ")";
	}
	friend istream& operator>>(istream& in, matrix& other)
	{
		return in >> other.row >> other.col;
	}
};

int solve(matrix arr[],int n)
{
	vector<vector<matrix>> ans(n+1,vector<matrix>());
	re(i, n)
		ans[1].push_back(arr[i]);
	//for (auto &i : ans[1])
		//cout << i << " ";
	//cout << endl;
	for (unsigned i = 2; i <= n; i++)//第i层。求连续i个矩阵相乘的最小子序列。
	{
		re(j, n - i + 1)//每层一共有n-i个矩阵
		{
			matrix min(0, 0, INT32_MAX);
			re(k, i - 1)//在第k个位置插空。一共有i-1个空。
				if (min.count() > ans[k + 1][j] + ans[i - k - 1][j + k + 1])
					min = ans[k + 1][j] * ans[i - k - 1][j + k + 1];
			//cout << min<<" ";
			ans[i].push_back(min);
		}
		//cout << endl;
	}
	return ans[n][0].count();
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
	try {
		/*主函数*/
		int n;
		matrix arr[1000];
		cin >> n;
		re(i, n)
			cin >> arr[i];

		cout << solve(arr,n) << endl;


	}
	catch (const char * error) { cout << error << endl; }
	cout << "运行时间：" << clock() - BeginTime << endl;
#ifndef DEBUG
	system("pause");
#endif // !DEBUG
	return 0;
}