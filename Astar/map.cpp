#include "map.h"
point location::end(1, 1), location::begin;

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
min_distance_(end-my_location_),
first_walk(9)
{}
location location::walk(int x)const
{
	if (x > 8 || x < 0)throw "Error";
	location ans(*this);
	ans.my_distance_++;
	ans.path[my_distance_] = my_location_;
	//ans.my_distance_ += map[my_location_.y][my_location_.x];//该点的速度。
	if (first_walk == 9)ans.first_walk = x;
	visit[my_location_.y][my_location_.x]=1;
	ans.my_location_ += vector[x];
	ans.min_distance_ = end - ans.my_location_;
	return ans;
}


bool location::can_walk(int x)const
{
	point temp = my_location_;
	temp += vector[x];
	if (map[temp.y][temp.x] == 0)
		return 0;
	int &vis_my = visit[temp.y][temp.x];
	if (vis_my == 0||vis_my>my_distance_+1)
	{
		vis_my = my_distance_ + 1;
		return 1;
	}
	return 0;
}

void Input()//地图从1，1到width,height
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

point search()
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
		map[temp.path[i].y][temp.path[i].x] = i;
	Output();
	return temp.First();
}