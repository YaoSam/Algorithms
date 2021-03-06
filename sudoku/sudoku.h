#pragma once
#include "iostream"
#include <bitset>
#define re(i,n) for(unsigned int i=0;i<n;i++)
#define Re(i,n) for(unsigned int i=1;i<=n;i++)
struct point{
	int x, y,value;
	point(int X=0, int Y=0,int V=0) :x(X), y(Y),value(V){}
	bool operator==(const point& other)const{ 
		return x == other.x&&y == other.y; 
	}
};
const point vector[4] = { point(1, 0), point(0, 1), point(-1, 0), point(0, -1) };
class sudoku{
	int empty;//记录空格的数目
	int map[10][10];
	std::bitset<10> visit[10][10];//代表是否能填某个数。
	point Find()const;
	void Write(int x, int y, int value);
	void logic_solve();//常规推理。最多推理两层。
	point FindEmpty()const;
public:
	sudoku();
	void clean();
	bool isError()const { return empty == -1; }
	bool isSolved()const{ return empty == 0; }
	friend std::istream& operator>>(std::istream &in, sudoku &other);
	friend std::ostream& operator<<(std::ostream &out, sudoku const &other);
	friend int main();
	void Solve();
};

std::istream& operator>>(std::istream &in, sudoku &other);
std::ostream& operator<<(std::ostream &out, sudoku const &other);

