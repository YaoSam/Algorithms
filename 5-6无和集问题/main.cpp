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
#include <time.h>
using namespace std;
#define DEBUG
#undef re
#define re(i,n) for(unsigned int i=0;i<n;i++)
const int MAX_Num = 100;

struct Number_list//����һ�����ּ���
{
	int Count;//�������ֵĸ���
	int number[MAX_Num];//��¼���������
	int Error_Number[MAX_Num*10];//��¼�Ѿ����ų�������
	Number_list() :
		Count(0)
	{
		memset(number, 0, sizeof(number));
		memset(number, 0, sizeof(Error_Number));
	}
	bool check(int const &n)const//�ж������Ƿ��ܷ���
	{
		return Error_Number[n]>0;
	}
	void push(int const &n)//�������֡�����ˢ��һ����͡�
	{
		re(i,Count)
			Error_Number[number[i] + n]++;
		number[Count++] = n;
	}
	void pop()
	{
		int temp = number[Count - 1];//��������
		re(i,Count-1)
			Error_Number[number[i] + temp]--;//����ɸ�������ɵ����
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
//ֻ�ܵ�58�ˡ���ܳ������
void dfs(int n,int k=1)
{
	re(i,n)//����n������
		if (list[i].check(k) == 0)//�ܷ���롣
		{
			list[i].push(k);
			if (k > max_k)//�ɹ���n�����������k�������µ����Ž⡣��¼��
			{
				max_k = k;
				re(j, n)ans[j] = list[j];
			}
			dfs(n, k + 1);//������һ����
			list[i].pop();//������
		}
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

	/*��������*/
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