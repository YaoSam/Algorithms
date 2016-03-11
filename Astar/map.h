#include "C:\Users\Sam\OneDrive\C++\数据结构汇总\Data Structure\Data Sturcture\heap.cpp"
#include <math.h>
int gcd(int x, int y);
class point{
	int x, y;
	int operator-(const point &other)const{
		return abs(x - other.x) + abs(y - other.y) - 1;
	}
};

class location{
	int walkable;
	int MyDistance, PreDistance;
	location *lastLocation;
	bool operator>(const location &other)const{
		return MyDistance + PreDistance > other.MyDistance + PreDistance; 
	}
};
location map[1000][1000];
MinHeap<location> one;

void search();