#include "map.h"
#include "..\Data Sturcture\queue.cpp"
#include <algorithm>
Vector location::end(1, 1), location::begin;

std::ostream& operator<<(std::ostream& out, const Vector &other)
{
	return out << "(" << other.x << "," << other.y << ")";
}


std::istream& operator>>(std::istream& in, Vector &other)
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
	//ans.path[my_distance_] = my_location_;
	//ans.my_distance_ += map[my_location_.y][my_location_.x];//该点的速度。
	if (first_walk == 9)ans.first_walk = x;
	ans.my_location_ += direction[x];
	ans.min_distance_ = end - ans.my_location_;
	return ans;
}


bool location::can_walk(int x)const
{
	Vector temp = my_location_;
	temp += direction[x];
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
		scanf_s("%d", &map[i + 1][j + 1]);
}
void Output()
{
	//std::cout << location::begin << location::end << std::endl;
	re(i, height)
	{
		re(j, width)
			printf_s("%2d", map[i + 1][j + 1]);
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

Vector search()
{
	int count = 0;
	ME::MinHeap<location> Heap;
	location temp(location::begin.x, location::begin.y);
	while (!temp.is_reach())
	{
		count++;
		re(i, 8)
			if (temp.can_walk(i))
				Heap.push(temp.walk(i));
		temp = Heap.pop();
	}
	int temp_width = width;
	printf("%d\n", visit[height - 1][width - 1]);
	std::for_each(visit, visit + height, [temp_width](auto a) {
		std::for_each(a, a + width, [](auto num){
			printf_s("%2d", num);
		});
		printf_s("\n");
	});
	//std::cout << std::endl;
	//int tempmap[1000][1000];
	//memcpy(tempmap, map, sizeof(map));
	//re(i, temp.my_distance_)
	//	map[temp.path[i].y][temp.path[i].x] = i;
	//Output();
	//memcpy(map, tempmap, sizeof(map));
	//std::cout << count << std::endl;
	return temp.First();
}

Vector search2()
{
	memset(visit, 0, sizeof(visit));
	int count = 0;
	ME::queue<location> Queue;
	location temp(location::begin.x, location::begin.y);
	Queue.push(temp);
	//while (!Queue.isEmpty())
	while (!temp.is_reach())
	{
		count++;
		re(i, 8)
			if (temp.can_walk(i))
				Queue.push(temp.walk(i));
		temp = Queue.pop();
	}
	printf("%d\n", visit[height - 1][width - 1]);
	int temp_width = width;
	std::for_each(visit, visit + height, [temp_width](auto a) {
		std::for_each(a, a + width, [](auto num) {
			printf_s("%2d", num);
		});
		printf_s("\n");
	});
	//re(i, height)
	//{
	//	re(j, width)
	//		if (visit[i + 1][j + 1]<10)
	//			std::cout << " " << visit[i + 1][j + 1] << " ";
	//		else
	//			std::cout << visit[i + 1][j + 1] << " ";
	//	std::cout << std::endl;
	//}
	//std::cout << std::endl;
	//Output();
	//std::cout << count << std::endl;
	return Vector(0, 0);
}