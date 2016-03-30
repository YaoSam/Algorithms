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


int num[5][1000000];
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
		clock_t my_Time[10], deltaTime; re(i, 4)my_Time[i+1] = 0;
		unsigned int n = 1000000;
		unsigned int Test_Time = 10;//���Դ���
		int k = n/1000;
		re(COUNT, Test_Time)
		{
			//���ɲ�������
			re(i, n)
			{
				//cin >> num[1][i];
				num[1][i] = rand();
			}
			//Qsort(num[1], 0, n - 1);
			//Qsort_MaxToMin(num[1], 0, n - 1);
			memcpy(num[2], num[1], sizeof(int)*n);
			memcpy(num[3], num[1], sizeof(int)*n);
			memcpy(num[4], num[1], sizeof(int)*n);
			//printArray(num[1], n);
			//cout << endl;
			//����knn

			deltaTime = clock();
			heapSort_knn(n, k, num[1]);
			my_Time[1] += clock() - deltaTime;

			deltaTime = clock();
			Qsort_knn(num[2], 0, n - 1, k);
			my_Time[2] += clock() - deltaTime;

			deltaTime = clock();
			super_knn(n, k, num[3]);
			my_Time[3] += clock() - deltaTime;

			deltaTime = clock();
			Qsort(num[3], 0, n - 1);
			my_Time[4] += clock() - deltaTime;

			//���򷽱�Աȡ�
			Qsort(num[1], 0, k - 1);
			Qsort(num[2], 0, k - 1);
			Qsort(num[3], 0, k - 1);
			re(i, k)
				if (num[1][i] != num[3][i]||num[1][i]!=num[2][i]/*||num[4][i]!=num[1][i]*/)
					throw "WTF!!!\n";
			//re(i, 4)
			//	printArray(num[i+1], n);
		}
		cout << "����ͨ����" << endl;
		cout << "����knn��ʱ��ֱ�Ϊ��" << endl;
		re(i, 4)
			cout << my_Time[i + 1] << " ";
	}
	catch (const char * error){ cout << error << endl; }
#ifndef DEBUG
	system("pause");
#endif // !DEBUG
	return 0;
}