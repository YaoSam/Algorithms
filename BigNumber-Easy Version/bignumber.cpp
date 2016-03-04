#pragma  once
#include "bignumber.h"
#include <math.h>
#include <sstream>
#include <iostream>
int* Number::Space(unsigned int n){
	int *ans = new int[n];
	memset(ans, 0, sizeof(int)*n);
	return ans;
}

void Number::Create(const std::string &str){
	if(num)delete[] num;
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

void Number::RightMove(){
	int count = 0;
	re(i, length){
		if (num[i] != 0)break;
		count++;
	}
	if (count > 0){
		int *tempNum = Space(length - count);
		memcpy(tempNum, num + count, sizeof(int)*(length - count));
		delete[] num;
		num = tempNum;
		Point += count;
		length -= count;
	}
}

Number::Number(const std::string &str):num(NULL){
	Create(str);
}

Number::Number(const Number& other):
length(other.length), sign(other.sign), Point(other.Point){
	num = new int[length];
	memcpy(num, other.num, sizeof(int)*length);
}

Number::Number(const double &number):num(NULL){
	std::stringstream ss;
	std::string str;
	ss << number;
	str = ss.str();
	Create(str);
}
Number::Number(const int & number):
num(NULL),
Point(0),
length(0),
sign(num<0){
	int tempNum[100] = { 0 };
	int n = abs(number);
	while (n > 0){
		tempNum[length++] = n % 10;
		n /= 10;
	}
	num = Space(length);
	memcpy(num, tempNum, sizeof(int)*length);
}


Number& Number::operator=(const Number& other){
	if (this == &other)
		return *this;
	delete[] num;
	length = other.length;
	sign = other.sign;
	Point = other.Point;
	num = new int[length];
	memcpy(num, other.num, sizeof(int)*length);
	return *this;
}

Number& Number::plus(const Number& other){
	int myLeft = Point + length, myRight = Point;//left就是最大位，right就是最小位。
	int otherLeft = other.Point + other.length, otherRight = other.Point;
	unsigned int newLength = Max(myLeft, otherLeft) - Min(myRight, otherRight) + 1;//整个位数
	int * tempNum = Space(newLength);
	//计算
	if (myRight <= otherRight){
		memcpy(tempNum, num, sizeof(int)*length);
		int delta = otherRight - myRight;//用来对齐位数
		int* otherNum = other.num;
		re(i, other.length){
			tempNum[i + delta] += otherNum[i];
		}
	}
	else{
		memcpy(tempNum, other.num, sizeof(int)*other.length);
		int delta = myRight - otherRight;
		re(i,length){
			tempNum[i + delta] += num[i];
		}
		Point = other.Point;
	}
	//进位
	re(i, newLength - 1)
		if (tempNum[i] >= 10){
			tempNum[i] %= 10;
			tempNum[i + 1]++;
		}
	if (tempNum[newLength - 1] == 0)
		newLength--;
	length = newLength;
	delete[] num;
	num = tempNum;
	RightMove();
	return *this;
}

Number& Number::subtract(const Number& other){
	int myLeft = Point + length, myRight = Point;
	int otherLeft = other.Point + other.length, otherRight = other.Point;
	unsigned int newLength = Max(myLeft, otherLeft) - Min(myRight, otherRight);//不用申请多一个位置了
	int * tempNum = Space(newLength);
	//计算
	if (myRight <= otherRight){
		memcpy(tempNum, num, sizeof(int)*length);
		int delta = otherRight - myRight;
		int* otherNum = other.num;
		re(i, other.length){
			tempNum[i + delta] -= otherNum[i];
		}
	}
	else{
		int delta = myRight - otherRight;
		memcpy(tempNum + delta, num, sizeof(int)*(length));
		int* otherNum = other.num;
		re(i, other.length){
			tempNum[i] -= otherNum[i];
		}
		Point = other.Point;
	}
	//调整正负
	re(i, newLength){
		if (tempNum[newLength - 1 - i] > 0)	break;
		if (tempNum[newLength - 1 - i] < 0){
			sign = !sign;
			newLength = newLength - i;
			re(j, newLength){
				tempNum[j] *= -1;
			}
			break;
		}
	}
	//退位
	re(i, newLength-1)//首位就不用考虑了
		if (tempNum[i] < 0){
			tempNum[i] += 10;
			tempNum[i + 1]--;
		}
	re(i, newLength)
		if (tempNum[newLength- i - 1] > 0){
			length = newLength - i;
			break;
		}
	delete[] num;
	num = tempNum;
	RightMove();
	return *this;
}

Number& Number::product(const Number& other){
	unsigned int NewLength = other.length + length;
	int *tempNum = Space(NewLength);
	re(i,other.length)
		if (other.num[i]>0)
			re(j, length){
			tempNum[i + j] += num[j] * other.num[i];
		}
	re(i, NewLength){//不是万进制。所以可以和计算过程分离。
		tempNum[i + 1] += tempNum[i] / 10;
		tempNum[i] %= 10;
	}
	re(i, NewLength){
		if (tempNum[NewLength - i - 1] > 0){
			length = NewLength - i;
			break;
		}
		if (i == NewLength - 1)length = 1;//特殊判断。
	}
	sign ^= other.sign;
	Point += other.Point;
	delete[] num;
	num = tempNum;
	return *this;
}

Number& Number::operator+=(const Number& other){
	if (sign == other.sign){
		return this->plus(other);
	}
	else{
		return this->subtract(other);
	}
}
Number& Number::operator-=(const Number& other){
	if (sign == other.sign){
		return this->subtract(other);
	}
	else{
		return this->plus(other);
	}
}
Number& Number::operator*=(const Number& other){
	return this->product(other);
}

bool Number::operator>(const Number& other)const{
	if (sign != other.sign)//先判断符号。
		return other.sign;
	int myLeft = Point + length,otherLeft=other.Point+other.length;
	if (myLeft != otherLeft)//判断长度
		return (myLeft > otherLeft) != sign;
	unsigned int i = 0;
	int minL = Min(length, other.length);
	while (i < minL){//判断每一位
		if (num[length - i - 1] != other.num[other.length - i - 1])
			return (num[length - i - 1] > other.num[other.length - i - 1]) != sign;
			i++;
		}
	return (i < length) != sign;
}

bool Number::operator==(const Number& other)const{
	if (sign != other.sign&&length != other.length&&Point!=other.Point)
		return false;
	re(i, length)//都相等了。直接比较
		if (other.num[i] != num[i])
			return false;
	return true;
}


std::ostream& operator<<(std::ostream &out, Number const &other){
	if (other.sign)
		out << '-';
	if (other.Point < 0){//有小数点
		if (unsigned int(abs(other.Point)) >= other.length){//小数点在前面
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
	return out;
}
std::istream& operator>>(std::istream &in, Number &other){
	std::string str;
	in >> str;
	other.Create(str);
	return in;
}

void Swap(Number &a, Number& b){
	Swap(a.Point, b.Point);
	Swap(a.length, b.length);
	Swap(a.num, b.num);
	Swap(a.sign, b.sign);
}
