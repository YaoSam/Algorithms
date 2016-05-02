#include <math.h>
#include "..\Data Sturcture\heap.cpp"
#include "..\Data Sturcture\normal.cpp"
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
		return ME::Max(abs(x - other.x), abs(y - other.y));
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
	//Vector path[1000];
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
static int map[1000][1000];
static int visit[1000][1000];
static unsigned int width, height;
void Input();
void Output();
Vector search();
Vector search2();