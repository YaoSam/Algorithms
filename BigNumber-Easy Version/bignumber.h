#pragma  once
#include "../BigNumber/common.cpp"
#include "string"

class BigNumber{
	int *num;
	unsigned int length;
	int Point;
	bool sign;
	int* Space(unsigned int n);
	void Create(const std::string &str);
	BigNumber&  plus(const BigNumber& other);
	BigNumber&  subtract(const BigNumber& other);
public:
	BigNumber() :num(new int(0)), length(1), Point(0), sign(0){}
	BigNumber(const std::string &str);
	BigNumber(const BigNumber& other);
	BigNumber& operator=(const BigNumber& other);
	~BigNumber(){ delete[] num; }
	BigNumber& operator+=(const BigNumber& other);
	BigNumber& operator-=(const BigNumber& other);
	BigNumber& operator*=(const BigNumber& other);
	friend std::ostream& operator<<(std::ostream &out, BigNumber const &other);
	friend void Swap(BigNumber &a, BigNumber& b);
};
std::ostream& operator<<(std::ostream &out, BigNumber const &other);
void Swap(BigNumber &a, BigNumber& b);
