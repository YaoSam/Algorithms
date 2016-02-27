#pragma once
#include "common.cpp"
#include <iostream>
#include <string>
const int ten[5] = { 0, 1, 10, 100, 1000 };		//用来进位的
const std::string zero[5] = {"", "0", "00", "000", "0000" };
class R
{
	bool sign;					//正负,true为负
	unsigned int length;	//数字的位数
	int point;					//起始位的位数。也就是*10^point
	int *data;					//数据段。
	unsigned int datasize;//数组的大小
	R(unsigned int L, int P, bool S, int *D,unsigned int DS) :
		length(L), sign(S), point(P), data(D),datasize(DS){}
	//简单常用函数
	int *EmptyIntSpace(unsigned int size)const;
	unsigned int getDigit(int num)const;//用来计算数字的位数。
	unsigned int getSize(int len)const{ return len / 4 + (len % 4 != 0); }
	void Create(std::string num);
	R& LeftMove(unsigned int dis);
	void AlignPoint(R &other);
	void clear();
	//两个整数的加减法，不考虑符号。
	R& plus(R& other);
	R& substract(R& other);
public:
	//基本函数
	R() :sign(0), length(0), point(0), data(NULL),datasize(0){}
	R(std::string num);
	R(double const &d);
	R(int const & n);
	R(const R & other);
	R& operator=(const R &other);
	virtual ~R(){ delete[] data; }
	friend std::ostream& operator<<(std::ostream &out, R const &other);//这玩意太TM烦了！！！
	friend std::istream& operator>>(std::istream &in, R & other);
	//数学运算符
	R& operator+=(const R & other);
	R& operator-=(const R & other);
	R& operator*=(const R & other);
	bool operator>(const R & other)const;
	bool operator==(const R & other)const;
};

std::ostream& operator<<(std::ostream &out, R const &other);
std::istream& operator>>(std::istream &in, R & other);
