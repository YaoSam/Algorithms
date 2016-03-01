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

struct point{
	int x, y;//x����y����
	point(int X = 0, int Y = 0) :x(X), y(Y){}
	bool operator==(point const &b){
		return x == b.x&&y == b.y;
	}
};
const point noPoint(-1, -1);
point search(int **chess, unsigned int left, unsigned int right, unsigned int up, unsigned int down){
	unsigned int n = right - left + 1;
	re(i, n){
		re(j, n){
			if (chess[i + up][j + left] != 0){
				return point(j + left, i + up);
			}
		}
	}
	return noPoint;
}

int Count = 0;
//0����հס�-1����ڿ顣
void Cover(int **chess, unsigned int left, unsigned int right, unsigned int up, unsigned int down){
	Count++;
	if (left > right)
		throw "�߽����";
	point blackPoint=search(chess, left, right, up, down);
	if (blackPoint == noPoint){
		return;
	}
	unsigned int midX = (left + right) / 2;
	unsigned int midY = (up + down) / 2;
	if (blackPoint.x > midX){//����м�ĵ㡣
		if (blackPoint.y > midY)
			chess[midY][midX] = chess[midY][midX + 1] = chess[midY + 1][midX] = Count;
		else
			chess[midY][midX] = chess[midY + 1][midX] = chess[midY + 1][midX + 1] = Count;
	}
	else{
		if (blackPoint.y > midY)
			chess[midY + 1][midX + 1] = chess[midY][midX] = chess[midY][midX + 1] = Count;
		else
			chess[midY + 1][midX] = chess[midY][midX + 1] = chess[midY + 1][midX + 1] = Count;
	}
	if (left == right-1)return;
	Cover(chess, left, midX, up, midY);//����
	Cover(chess, midX+1, right, up, midY);//����
	Cover(chess, left, midX, midY+1, down);//����
	Cover(chess, midX+1, right, midY+1, down);//����
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
		int n, x, y;
		cin >> n >> x >> y;
		//��ֵ
		unsigned int width = 1;//�����εı߳�
		re(i, n){
			width <<= 2;//4^n
		}
		int **map = new int *[width];
		re(i, width){
			map[i] = new int[width];
			memset(map[i], 0, sizeof(int)*width);
		}
		map[y][x] = -1;
		//�����ʼ��Chess
		re(i, width){
			re(j, width){
				if (map[i][j] < 10&&map[i][j]>=0)
					cout << 0;
				cout << map[i][j] << " ";
			}
			cout << endl;
		}
		Cover(map, 0, width-1, 0, width-1);
		re(i, width){
			re(j, width){
				if (map[i][j] < 10 && map[i][j] >= 0)
					cout << 0;
				cout << map[i][j] << " ";
			}
			cout << endl;
		}
	}
	catch (const char * error){ cout << error << endl; }
#ifndef DEBUG
	system("pause");
#endif // !DEBUG
	return 0;
}