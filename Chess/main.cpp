/*
*　　　　　　　　┏┓　　　┏┓+ +
*　　　　　　　┏┛┻━━━┛┻┓ + +
*　　　　　　　┃　　　　　　　┃ 　
*　　　　　　　┃　　　━　　　┃ ++ + + +
*　　　　　　 ████━████ ┃+
*　　　　　　　┃　　　　　　　┃ +
*　　　　　　　┃　　　┻　　　┃
*　　　　　　　┃　　　　　　　┃ + +
*　　　　　　　┗━┓　　　┏━┛
*　　　　　　　　　┃　　　┃　　　　　　　　　　　
*　　　　　　　　　┃　　　┃ + + + +
*　　　　　　　　　┃　　　┃　　　　Code is far away from bug with the animal protecting　　　　　　　
*　　　　　　　　　┃　　　┃ + 　　　　神兽保佑,代码无bug　　
*　　　　　　　　　┃　　　┃
*　　　　　　　　　┃　　　┃　　+　　　　　　　　　
*　　　　　　　　　┃　 　　┗━━━┓ + +
*　　　　　　　　　┃ 　　　　　　　┣┓
*　　　　　　　　　┃ 　　　　　　　┏┛
*　　　　　　　　　┗┓┓┏━┳┓┏┛ + + + +
*　　　　　　　　　　┃┫┫　┃┫┫
*　　　　　　　　　　┗┻┛　┗┻┛+ + + +
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
	int x, y;//x横向，y纵向
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
//0代表空白。-1代表黑块。
void Cover(int **chess, unsigned int left, unsigned int right, unsigned int up, unsigned int down){
	Count++;
	if (left > right)
		throw "边界出错";
	point blackPoint=search(chess, left, right, up, down);
	if (blackPoint == noPoint){
		return;
	}
	unsigned int midX = (left + right) / 2;
	unsigned int midY = (up + down) / 2;
	if (blackPoint.x > midX){//标记中间的点。
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
	Cover(chess, left, midX, up, midY);//上左
	Cover(chess, midX+1, right, up, midY);//上右
	Cover(chess, left, midX, midY+1, down);//下左
	Cover(chess, midX+1, right, midY+1, down);//下右
}

int main()
{
	clock_t BeginTime = clock();
	srand(unsigned(time(NULL)));
#ifdef DEBUG
	FILE *input, *output; //没用的指针... ...
	freopen_s(&input, "in.txt", "r", stdin);
	freopen_s(&output, "out.txt", "w", stdout);
#endif
	try{
		int n, x, y;
		cin >> n >> x >> y;
		//赋值
		unsigned int width = 1;//正方形的边长
		re(i, n){
			width <<= 2;//4^n
		}
		int **map = new int *[width];
		re(i, width){
			map[i] = new int[width];
			memset(map[i], 0, sizeof(int)*width);
		}
		map[y][x] = -1;
		//输出初始的Chess
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