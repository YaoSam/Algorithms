#pragma  once
#include "../BigNumber/common.cpp"
#include "string"

class Number{
	int *num;
	unsigned int length;
	int Point;
	bool sign;
	int* Space(unsigned int n);
	void Create(const std::string &str);
	Number&  plus(const Number& other);
	Number&  subtract(const Number& other);
	Number&  product(const Number& other);
	void RightMove();//将多余的0去掉。
public:
	Number() :num(new int(0)), length(1), Point(0), sign(0){}
	Number(const std::string &str);
	Number(const double &num);
	Number(const int & number);
	Number(const Number& other);
	Number& operator=(const Number& other);
	~Number(){ delete[] num; }
	Number& operator+=(const Number& other);
	Number& operator-=(const Number& other);
	Number& operator*=(const Number& other);
	bool operator>(const Number& other)const;
	bool operator==(const Number& other)const;
	friend std::ostream& operator<<(std::ostream &out, Number const &other);
	friend std::istream& operator>>(std::istream &in, Number &other);
	friend void Swap(Number &a, Number& b);
};
std::ostream& operator<<(std::ostream &out, Number const &other);
std::istream& operator>>(std::istream &in, Number  &other);
void Swap(Number &a, Number& b);
