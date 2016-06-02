/*
*������������������������������+ +
*�������������������ߩ��������ߩ� + +
*�������������������������������� ��
*�������������������������������� ++ + + +
*������������ ������������������ ��+
*�������������������������������� +
*�����������������������ߡ�������
*�������������������������������� + +
*��������������������������������
*��������������������������������������������������
*���������������������������� + + + +
*������������������������������������Code is far away from bug with the animal protecting��������������
*���������������������������� + �����������ޱ���,������bug����
*����������������������������
*��������������������������������+������������������
*���������������������� �������������� + +
*�������������������� ���������������ǩ�
*�������������������� ������������������
*�����������������������������ש����� + + + +
*�����������������������ϩϡ����ϩ�
*�����������������������ߩ������ߩ�+ + + +
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
		if (col != other.row)throw"������Ŀ��ͬ���������";
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
	for (unsigned i = 2; i <= n; i++)//��i�㡣������i��������˵���С�����С�
	{
		re(j, n - i + 1)//ÿ��һ����n-i������
		{
			matrix min(0, 0, INT32_MAX);
			re(k, i - 1)//�ڵ�k��λ�ò�ա�һ����i-1���ա�
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
	FILE *input, *output; //û�õ�ָ��... ...
	freopen_s(&input, "in.txt", "r", stdin);
	freopen_s(&output, "out.txt", "w", stdout);
#endif
	try {
		/*������*/
		int n;
		matrix arr[1000];
		cin >> n;
		re(i, n)
			cin >> arr[i];

		cout << solve(arr,n) << endl;


	}
	catch (const char * error) { cout << error << endl; }
	cout << "����ʱ�䣺" << clock() - BeginTime << endl;
#ifndef DEBUG
	system("pause");
#endif // !DEBUG
	return 0;
}