#include <math.h>
#include "C:\Users\Sam\OneDrive\C++\数据结构汇总\Data Structure\Data Sturcture\heap.cpp"
#include "C:\Users\Sam\OneDrive\C++\数据结构汇总\Data Structure\Data Sturcture\queue.cpp"
#include "C:\Users\Sam\OneDrive\C++\数据结构汇总\Data Structure\Data Sturcture\normal.cpp"
struct Vector
{
	int x, y;
	Vector(int X=0, int Y=0) :x(X), y(Y){}
	Vector &operator+=(const Vector & other){
		x += other.x;
		y += other.y;
		return *this;
	}
	bool operator==(const Vector& other)const
	{
		return x == other.x&&y == other.y;
	}
	int operator-(const Vector &other)const//计算距离理论最小值
	{
		return Max(abs(x - other.x), abs(y - other.y));
	}
};
std::ostream& operator<<(std::ostream& out,const Vector &other);
std::istream& operator>>(std::istream& in, Vector &other);
const Vector direction[8] = 
{ 
	Vector(0, 1), Vector(0, -1), Vector(1, 0), Vector(-1, 0), 
	Vector(1, 1), Vector(-1, -1), Vector(-1, 1), Vector(1, -1) 
};

/////////////////////////////////////////////////////////////

class location
{
public:
	Vector my_location_;
	unsigned int my_distance_, min_distance_;
	int first_walk;
	Vector path[100];
	static Vector end;
	static Vector begin;
	location(int x=0, int y=0);
	location walk(int x)const;
	Vector First()const{ return direction[first_walk]; }
	bool can_walk(int x)const;
	bool is_reach()const{ return my_location_ == end; }
	bool operator>(const location &other)const{
		return my_distance_ + min_distance_ > other.my_distance_ + other.min_distance_; 
	}
	int dis()const{ return my_distance_; }
};
static int map[100][100];
static int tempmap[100][100];
static int visit[100][100];
static unsigned int width, height;
void Input();
void Output();
Vector search();
Vector search2();