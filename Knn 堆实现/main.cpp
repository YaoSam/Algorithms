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
#include "knn.cpp"

using namespace std;
#undef re
#define re(i,n) for(unsigned int i=0;i<n;i++)
#define DEBUG
extern int TIME;
int main()
{
	clock_t BeginTime =	clock();
	srand(unsigned(time(NULL)));
#ifdef DEBUG
	FILE *input, *output; //û�õ�ָ��... ...
	freopen_s(&input, "in.txt", "r", stdin);
	freopen_s(&output, "out.txt", "w", stdout);
#endif
	try{
		
		unsigned int n = 1000;
		int num1[10000], num2[10000],num3[10000];
		unsigned int Test_Time = 100;//���Դ���
		re(COUNT, Test_Time)
		{
			re(i, n)
			{
				//cin >> num1[i];
				num1[i] = rand() % 100;
			}
			memcpy(num2, num1, sizeof(int)*n);
			memcpy(num3, num1, sizeof(int)*n);
			//printArray(num1, n);
			//cout << endl;
			int k = 20;
			Qsort_knn(num1, 0, n - 1, k);
			knn(n, k, num2);
			Qsort(num3, 0, n - 1);
			//���򷽱�Աȡ�
			Qsort(num1, 0, k - 1);
			Qsort(num2, 0, k - 1);
			re(i, k)
				if (num1[i] != num3[i]||num1[i]!=num2[i])
					throw "WTF!!!\n";
			//printArray(num1, k);
			//printArray(num2, k);
			//printArray(num3, k);
		}
		cout << "����ͨ����" << endl;
	}
	catch (const char * error){ cout << error << endl; }
#ifndef DEBUG
	system("pause");
#endif // !DEBUG
	return 0;
}