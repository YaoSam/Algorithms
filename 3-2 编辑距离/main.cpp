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
using namespace std;
#undef re
#define re(i,n) for(unsigned int i=0;i<n;i++)
#define DEBUG

template<class T>
const T& MIN(const T&a, const T&b,const T& c)
{
	return (a < b ? a : b) < c ? a : c;
}
int solve(const string &a, const string &b)
{
	int min[100][100];
	memset(min, 0, sizeof(min));
	int length1 = a.length(), length2 = b.length();
	min[0][0] = a[0] == b[0];
	min[1][0] = a[1] == b[0];
	min[0][1] = a[0] == b[1];
	for (unsigned i = 1; i < length1; i++)
		for (unsigned j = 1; j < length2; j++)
			min[i][j] = MIN(
				min[i - 1][j - 1] + (a[i] == b[j]),
				min[i - 1][j],
				min[i][j - 1]
			);
	return length1 > length2 ? length1 : length2 - min[length1 - 1][length2 - 1];
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
		string a, b;
		cin >> a >> b;
		cout << solve(a, b);


	}
	catch (const char * error) { cout << error << endl; }
	cout << "����ʱ�䣺" << clock() - BeginTime << endl;
#ifndef DEBUG
	system("pause");
#endif // !DEBUG
	return 0;
}