#include "../Data Sturcture/array.cpp"
#include <ostream>
const int MaxNumber = 1000;

struct object
{
	unsigned int num,weight;
	float value;
	object(float v=0.0, unsigned int w=0, unsigned int n = 1) :value(v), weight(w), num(n){}
};

inline std::ostream& operator<<(std::ostream& out, const object &other)
{
	if (other.num > 0)
		return out << '(' << other.value / other.num << ',' << other.weight / other.num << ',' << other.num << ')';
	else
		return out << '(' << other.value << ',' << other.weight << ')';
}

inline std::istream& operator>>(std::istream& in, object& other)
{
	return in >> other.value >> other.weight >> other.num;
}


class bag
{
	unsigned int Max_weight;//背包的最大空间。
	float ValueOfBag[MaxNumber];
	array<object> solution[MaxNumber];//随便就用栈来储存了。好像也没什么不好。
public:
	float Onebag(const object &one);
	float Twobag(const object &one);
	float Threebag(const object &one);
	float groupbag(const object one[],unsigned int n);
public:
	bag(unsigned int Limit) :Max_weight(Limit){ memset(ValueOfBag, 0, sizeof(ValueOfBag)); }
	float push(object const &one);
	array<object> Solution(unsigned int n=0);
};