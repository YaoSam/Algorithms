#include "map.h"
point location::end(1, 1), location::begin;
int gcd(int x, int y)
{
	return y > 0 ? gcd(y, x%y) : x;
}

int point::operator-(const point &other)const{
	int deltaX = abs(x - other.x), deltaY = abs(y - other.y);
	if (deltaX == 0)return deltaY;
	if (deltaY == 0)return deltaX;
	int common = gcd(deltaX, deltaY);
	return common*(deltaX / common + deltaY / common - 1);
}
std::ostream& operator<<(std::ostream& out, const point &other)
{
	return out << "(" << other.x << "," << other.y << ")";
}


std::istream& operator>>(std::istream& in, point &other)
{
	return in >> other.x >> other.y;
}


location::location(int x, int y):
my_location_(x, y),
my_distance_(0),
min_distance_(end-my_location_)
{}
location location::walk(int x)const
{
	if (x > 8 || x < 0)throw "Error";
	location ans(*this);
	ans.path[ans.my_distance_++] = my_location_;
	//ans.my_distance_ += map[my_location_.y][my_location_.x];
	visit[my_location_.y][my_location_.x]=1;
	ans.my_location_ += vector[x];
	ans.min_distance_ = end - ans.my_location_;
	return ans;
}


bool location::can_walk(int x)const
{
	point temp = my_location_;
	temp += vector[x];
	return map[temp.y][temp.x];
}

void Input()//µØÍ¼´Ó1£¬1µ½width,height
{
	memset(visit, 0, sizeof(visit));
	std::cin >> width >> height;
	std::cin >> (location::begin) >> (location::end);
	memset(map, 0, sizeof(map));
	re(i, height)
		re(j, width)
		std::cin >> map[i+1][j+1];
}
void Output()
{
	//std::cout << location::begin << location::end << std::endl;
	re(i, height)
	{
		re(j, width)
			if (map[i + 1][j+1]<10)
				std::cout <<" "<< map[i + 1][j + 1] << " ";
			else
				std::cout << map[i + 1][j + 1] << " ";
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void search()
{
	MinHeap<location> Heap;
	location temp(location::begin.x, location::begin.y);
	while (!temp.is_reach())
	{
		re(i, 8)
			if (temp.can_walk(i))
				Heap.push(temp.walk(i));
		temp = Heap.pop();
	}
	re(i, temp.my_distance_)
		map[temp.path[i].y][temp.path[i].x] = i + 1;
	re(i, height)
	{
		re(j, width)
			std::cout << visit[i + 1][j + 1] << " ";
		std::cout << std::endl;
	}
	std::cout << std::endl;

	Output();
	std::cout << temp.dis() << std::endl;
}