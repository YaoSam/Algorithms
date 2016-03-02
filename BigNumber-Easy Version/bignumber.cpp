#pragma  once
#include "bignumber.h"
#include <math.h>
#include <sstream>
#include <iostream>
int* BigNumber::Space(unsigned int n){
	int *ans = new int[n];
	memset(ans, 0, sizeof(int)*n);
	return ans;
}

void BigNumber::Create(const std::string &str){
	sign = (str[0] == '-');
	std::string temp = str;
	unsigned int strLen, left = 0, right = temp.length();
	if (sign)
		temp = temp.substr(1, temp.length());
	strLen = temp.length();
	Point = temp.find('.');
	if (Point>= 0){
		temp = temp.substr(0, Point) + temp.substr(Point + 1, temp.length());
		strLen--;
	}
	else Point = strLen;
	re(i, strLen)
		if (temp[strLen - i - 1] != '0'){
			right = strLen - i - 1;
			break;
		}
	re(i,strLen)
		if (temp[i] != '0'){
			left = i;
			break;
		}
	Point -= right+1;
	temp = temp.substr(left, right - left+1);//因为right也不为0。所以要加一。
	//录入数据
	length = temp.length();
	num = Space(length);
	re(i,length)
		num[i] = temp[length - i-1] - '0';
}

BigNumber::BigNumber(const std::string &str){
	Create(str);
}

BigNumber::BigNumber(const BigNumber& other):
length(other.length), sign(other.sign), Point(other.Point){
	num = new int[length];
	memcpy(num, other.num, sizeof(int)*length);
}

BigNumber& BigNumber::operator=(const BigNumber& other){
	if (this == &other)
		return *this;
	delete[] num;
	length = other.length;
	sign = other.sign;
	Point = other.Point;
	num = new int[length];
	memcpy(num, other.num, sizeof(int)*length);
}

BigNumber& BigNumber::operator+=(const BigNumber& other){
	unsigned int NewLength = Max(length, other.length) + 1;
	if (Point > other.Point){

	}
	else if (Point < other.Point){

	}
	else{
		memcpy()
	}


}


std::ostream& operator<<(std::ostream &out, BigNumber const &other){
	if (other.sign)
		out << '-';
	if (other.Point < 0){//有小数点
		if (abs(other.Point) >= other.length){//小数点在前面
			unsigned int length = other.length;
			std::string str;
			out << "0.";
			str.assign(abs(other.Point) - other.length, '0');
			out << str;
			re(i, length)
				out << other.num[length - i - 1];
		}
		else{//小数点在中间
			int point = -other.Point;
			unsigned int length = other.length;
			re(i, length){
				if (length - i == point)
					out << '.';
				out << other.num[length - i - 1];
			}
		}
	}
	else{//没有小数点。有补零。
		unsigned int length = other.length;
		std::string str;
		re(i, length)
			out << other.num[length - i - 1];
		str.assign(other.Point, '0');
		out << str;
	}
	return out << std::endl;
}

void Swap(BigNumber &a, BigNumber& b){
	Swap(a.Point, b.Point);
	Swap(a.length, b.length);
	Swap(a.num, b.num);
	Swap(a.sign, b.sign);
}
