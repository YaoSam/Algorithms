#include <math.h>
#include "C:\Users\Sam\OneDrive\C++\数据结构汇总\Data Structure\Data Sturcture\heap.cpp"
#include "C:\Users\Sam\OneDrive\C++\数据结构汇总\Data Structure\Data Sturcture\stack.cpp"
#include "C:\Users\Sam\OneDrive\C++\数据结构汇总\Data Structure\Data Sturcture\normal.cpp"
int gcd(int x, int y);
struct point
{
	int x, y;
	point(int X=0, int Y=0) :x(X), y(Y){}
	point &operator+=(const point & other){
		x += other.x;
		y += other.y;
		return *this;
	}
	bool operator==(const point& other)const
	{
		return x == other.x&&y == other.y;
	}
	int operator-(const point &other)const;
};
std::ostream& operator<<(std::ostream& out,const point &other);
std::istream& operator>>(std::istream& in, point &other);
const point vector[8] = //八个方向
{ 
	point(0, 1), point(1, 0), point(0, -1), point(-1, 0), 
	point(1, 1), point(1, -1), point(-1, 1), point(-1, -1) 
};

/////////////////////////////////////////////////////////////

class location{
public:
	point my_location_;
	int my_distance_, min_distance_;
	point path[100];
	static point begin;
	static point end;
public:
	location(int x=0, int y=0);
	location walk(int x)const;
	bool can_walk(int x)const;
	bool is_reach()const{ return my_location_ == end; }
	bool operator>(const location &other)const{
		return my_distance_ + min_distance_ > other.my_distance_ + other.min_distance_; 
	}
	int dis()const{ return my_distance_ + min_distance_; }
};
static int map[100][100];
static int visit[100][100];
static int width, height;
void Input();
void Output();
void search();