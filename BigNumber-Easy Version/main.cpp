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
#include "BigNumber.h"
using namespace std;
#undef re
#define re(i,n) for(unsigned int i=0;i<n;i++)
#define DEBUG
void Test();

int main()
{
	clock_t BeginTime = clock();
	srand(unsigned(time(NULL)));
#ifdef DEBUG
	FILE *input, *output; //û�õ�ָ��... ...
	freopen_s(&input, "in.txt", "r", stdin);
	freopen_s(&output, "out.txt", "w", stdout);
#endif
	try{
		string a, b;
		while (cin >> a >> b){
			BigNumber one(a), two(b);
			cout << one << two ;
			cout << (one -= two) << endl;
		}
	}
	catch (const char * error){ cout << error << endl; }
#ifndef DEBUG
	system("pause");
#endif // !DEBUG
	return 0;
}