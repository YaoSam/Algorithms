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
#include "../Data Sturcture/array.cpp"
#include "bag.h"
using namespace std;
#define DEBUG
#undef re
#define re(i,n) for(unsigned int i=0;i<n;i++)


int main()
{
	clock_t BeginTime = clock();
	srand(unsigned(time(nullptr)));
#ifdef DEBUG
	FILE *input, *output; //û�õ�ָ��... ...
	freopen_s(&input, "in.txt", "r", stdin);
	freopen_s(&output, "out.txt", "w", stdout);
#endif

	/*��������*/
	unsigned int n,weight;
	cin >> n>>weight;
	bag one(weight);
	object temp[100];
	re(i,n)
	{
		cin >> temp[0];
		cout << one.push(temp[0]) << endl;
		cout << one.Solution();
	}
	cin >> n;
	re(i, n)
	{
		cin >> temp[i];
		//cout<<one.push(temp)<<endl;
	}
	cout<<one.groupbag(temp, n)<<endl;
	cout << one.Solution();

	cout << "����ʱ�䣺" << (clock() - BeginTime) << endl;
#ifndef DEBUG
	system("pause");
#endif // !DEBUG
	return 0;
}