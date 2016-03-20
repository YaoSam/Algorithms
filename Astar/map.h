#include <math.h>
#include "C:\Users\Sam\OneDrive\C++\数据结构汇总\Data Structure\Data Sturcture\heap.cpp"
#include "C:\Users\Sam\OneDrive\C++\数据结构汇总\Data Structure\Data Sturcture\normal.cpp"
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
	int operator-(const point &other)const//计算距离理论最小值
	{
		return Max(abs(x - other.x), abs(y - other.y));
	}
};
std::ostream& operator<<(std::ostream& out,const point &other);
std::istream& operator>>(std::istream& in, point &other);
const point vector[8] = //八个方向，顺时针。
{ 
	point(0, -1), point(1, -1), point(1, 0), point(1, 1), 
	point(0, 1), point(-1, 1), point(-1, 0), point(-1, -1) 
};

/////////////////////////////////////////////////////////////

class location
{
public:
	point my_location_;
	unsigned int my_distance_, min_distance_;
	int first_walk;
	point path[50];
	static point end;
	static point begin;
	location(int x=0, int y=0);
	location walk(int x)const;
	point First()const{ return vector[first_walk]; }
	bool can_walk(int x)const;
	bool is_reach()const{ return my_location_ == end; }
	bool operator>(const location &other)const{
		return my_distance_ + min_distance_ > other.my_distance_ + other.min_distance_; 
	}
	int dis()const{ return my_distance_ + min_distance_; }
};
static int map[100][100];
static int visit[100][100];
static unsigned int width, height;
void Input();
void Output();
point search();