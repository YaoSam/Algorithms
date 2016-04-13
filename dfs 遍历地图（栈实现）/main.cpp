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
#include "C:\Users\Sam\Documents\C++\���ݽṹ����\Data Structure\Data Sturcture\Stack.cpp"
#include "C:\Users\Sam\Documents\C++\���ݽṹ����\Data Structure\Data Sturcture\ALL.h"
using namespace std;
#define DEBUG
#undef re
#define re(i,n) for(unsigned int i=0;i<n;i++)

struct Vector
{
	int y, x,i;//����һ��i������ʶ���Ǹ����������ġ�
	Vector(int y = 0, int x = 0, int i = 0) :x(x), y(y), i(i){}
	bool operator==(const Vector& other)const{ return x == other.x&&y == other.y; }
	Vector operator+(const Vector & other)const{ return Vector(y + other.y, x + other.x,i); }
	Vector operator-(const Vector & other)const{ return Vector(y - other.y, x - other.x, i); }
	Vector& operator+=(const Vector & other){ x += other.x, y += other.y; return *this; }//���Ч�ʸ���
	Vector& operator-=(const Vector & other){ x -= other.x, y -= other.y; return *this; }
};
ostream& operator<<(ostream& out, const Vector & other)
{
	return out << '(' << other.x << ',' << other.y << ')';
}
istream& operator>>(istream& in, Vector & other)
{
	return in >> other.y >> other.x;
}
int map[20][20] = { 0 };
int visit[20][20] = { 0 };
unsigned int height = 0, width = 0;
const Vector direction[8] =
{
	Vector(1, 0), Vector(-1, 0), Vector(0, 1), Vector(0, -1),
	Vector(1, 1), Vector(1, -1), Vector(-1, 1), Vector(-1, -1),
};
void Input()
{
	re(i, height)
		re(j, width)
		cin >> map[i][j];
}

void Output()
{
	re(i, height)
	{
		re(j, width)
		{
			if (visit[i][j] < 10)
				cout << ' ';
			cout << visit[i][j] << ' ';
		}
		cout << endl;
	}
	cout << endl;
}

bool Judge(const Vector &one)
{
	return 0 <= one.y && 0 <= one.x&&one.y < height&&one.x < width&&map[one.y][one.x] == 0 && visit[one.y][one.x] == 0;
}

int Dfs(const Vector &Begin,const Vector &End)//ģ�¶�������ǰ�����
{
	stack<Vector> Stack,solution;
	int count = 0;
	Vector temp = Begin;
	const int direction_number = 8;
	while (Judge(temp) || !Stack.isEmpty())
	{
		while (Judge(temp)&&temp.i<direction_number)
		{
			if (temp == End)
			{
				if (solution.isEmpty() || solution.Top() > Stack.Top())
				{
					count++;
					solution = Stack;
					cout << solution;
					Output();
				}
			}
			Stack.push(temp);
			visit[temp.y][temp.x] = Stack.Top() + 1;//���ջ����ġ�
			temp.i = 0;
			temp += direction[0];//һֱ��������ӱ�����
		}
		if(!Stack.isEmpty())
		{
			while (((!solution.isEmpty() && solution.Top() <= Stack.Top()) //��������ɸѡ
				||temp.i == direction_number-1) && !Stack.isEmpty())//�Ƿ�������ұ���
			{
				temp = Stack.pop();//�����ԣ��򷵻���һ��
				visit[temp.y][temp.x] = 0;//ȡ��ջ���
			}
			cout << temp.i << endl;
			(temp-=direction[temp.i])+=direction[temp.i + 1];//������
			temp.i++;//��¼��ǰ�ķ���
			cout << temp << endl;

		}
	}
	return count;
}

int times = 0;
int Dfs(const Vector &Begin,const Vector &End,const Vector &next,int my_time=0)//�ݹ�������Ч�ʸߺܶ�ġ�
{
	if ((times > 0 && my_time >= times)||!Judge(next))return 0;
	int ans = 0;
	if (next == End)
	{
		Output();
		times = my_time;
		return 1;
	}
	re(i, 8)
	{
		visit[next.y][next.x] = my_time + 1;
		 ans+=Dfs(Begin,End,next + direction[i], my_time + 1);
		visit[next.y][next.x] = 0;
	}
	return ans;
}


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
	Vector Begin, End;
	cin >> height >> width;
	cin >> Begin >> End;
	Input();
	clock_t time1 = clock();
	cout<<Dfs(Begin, End)<<endl;
	cout <<"����ʱ��: "<< clock() - time1 << endl;

	memset(visit, 0, sizeof(visit));

	time1 = clock();
	cout << Dfs(Begin, End, Begin)<<endl;
	cout << "����ʱ��: " << clock() - time1 << endl;

	cout << "����ʱ�䣺" << (clock() - BeginTime) << endl;
#ifndef DEBUG
	system("pause");
#endif // !DEBUG
	return 0;
}