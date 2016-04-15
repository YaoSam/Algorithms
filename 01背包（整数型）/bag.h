#include "../Data Sturcture/array.cpp"
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
	if (other.num > 0)
		return out << '(' << other.value / other.num << ',' << other.weight / other.num << ',' << other.num << ')';
	else
		return out << '(' << other.value << ',' << other.weight << ')';
}

inline std::istream& operator>>(std::istream& in, object_1d& other)
{
	return in >> other.value >> other.weight >> other.num;
}


class bag_1d
{
	int Max_weight;//���������ռ䡣
	float ValueOfBag[MaxNumber];
	array<object_1d> solution[MaxNumber];//������ջ�������ˡ�����Ҳûʲô���á�
public:
	float Onebag(const object_1d &one);
	float Twobag(const object_1d &one);
	float Threebag(const object_1d &one);
	float groupbag(const object_1d one[],unsigned int n);
public:
	bag_1d(int Limit) :Max_weight(Limit){ memset(ValueOfBag, 0, sizeof(ValueOfBag)); }
	float push(object_1d const &one);
	array<object_1d> Solution(unsigned int n=0);
};