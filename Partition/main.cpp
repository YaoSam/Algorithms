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
void Partition(T const a[], int size, int k = 0){
	static int Stack[100] = { 0 };
	static int Count = 0;//Count�൱��ջ����Ķ���Ԫ�ء�
	//Core
	if (k < size){
		for (int i = k; i < size; i++){
			Stack[Count++] = i;
			Partition(a, size, i+1);
		}
	}
	else{//���ջ
		int j = 0;
		cout << "|";
		re(i, size)
			if (i == Stack[j]){
				cout << a[i]<< "|";
				j++;
			}
			else
				cout << a[i] << " ";
		cout << endl;
	}
	Count--;
	if (k == 0)Count = 0;//ֻ�е�һ��kΪ1.�ݹ����������count��
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
	try{
		int n;
		cin >> n;
		string a[1000];
		re(i, n)
			cin >> a[i];
		Partition(a, n);
		cout << endl;
		Partition(a+1, n - 1);
	}
	catch (const char * error){ cout << error << endl; }
	cout << endl << "����ʱ�䣺" << clock() - BeginTime << endl;
#ifndef DEBUG
	system("pause");
#endif // !DEBUG
	return 0;
}