#include "../Data Sturcture/array.h"
#include <ostream>
const int MaxNumber = 1000;

struct object_1d
{
	unsigned int num,weight;
	float value;
	object_1d(float v=0.0, unsigned int w=0, unsigned int n = 1) :value(v), weight(w), num(n){}
};

inline std::ostream& operator<<(std::ostream& out, const object_1d &other)
{
	return out << '(' << other.value << ',' << other.weight << ')';
}

inline std::istream& operator>>(std::istream& in, object_1d& other)
{
	return in >> other.value >> other.weight >> other.num;
}


class bag_1d
{
	int Max_weight;//背包的最大空间。
	float ValueOfBag[MaxNumber];
	array<object_1d> solution[MaxNumber];//随便就用栈来储存了。好像也没什么不好。
	void Onebag(const object_1d &one);
	void Twobag(const object_1d &one);
	void Threebag(const object_1d &one);
public:
	bag_1d(int Limit) :Max_weight(Limit){ memset(ValueOfBag, 0, sizeof(ValueOfBag)); }
	float push(object_1d const &one);
	array<object_1d> Solution(unsigned int n=0);
};