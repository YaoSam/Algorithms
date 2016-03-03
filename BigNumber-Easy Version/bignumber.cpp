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
	temp = temp.substr(left, right - left+1);//��ΪrightҲ��Ϊ0������Ҫ��һ��
	//¼������
	length = temp.length();
	num = Space(length);
	re(i,length)
		num[i] = temp[length - i-1] - '0';
}

void BigNumber::RightMove(){
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

BigNumber& BigNumber::plus(const BigNumber& other){
	int myLeft = Point + length, myRight = Point;//left�������λ��right������Сλ��
	int otherLeft = other.Point + other.length, otherRight = other.Point;
	int newLength = Max(myLeft, otherLeft) - Min(myRight, otherRight) + 1;//����λ��
	int * tempNum = Space(newLength);
	//����
	if (myRight <= otherRight){
		memcpy(tempNum, num, sizeof(int)*length);
		int delta = otherRight - myRight;//��������λ��
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
	//��λ
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

BigNumber& BigNumber::subtract(const BigNumber& other){
	int myLeft = Point + length, myRight = Point;
	int otherLeft = other.Point + other.length, otherRight = other.Point;
	int newLength = Max(myLeft, otherLeft) - Min(myRight, otherRight);//���������һ��λ����
	int * tempNum = Space(newLength);
	//����
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
	//��������
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
	//��λ
	re(i, newLength-1)//��λ�Ͳ��ÿ�����
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

BigNumber& BigNumber::operator+=(const BigNumber& other){
	if (sign == other.sign){
		return this->plus(other);
	}
	else{
		return this->subtract(other);
	}
}
BigNumber& BigNumber::operator-=(const BigNumber& other){
	if (sign == other.sign){
		return this->subtract(other);
	}
	else{
		return this->plus(other);
	}
}


std::ostream& operator<<(std::ostream &out, BigNumber const &other){
	if (other.sign)
		out << '-';
	if (other.Point < 0){//��С����
		if (abs(other.Point) >= other.length){//С������ǰ��
			unsigned int length = other.length;
			std::string str;
			out << "0.";
			str.assign(abs(other.Point) - other.length, '0');
			out << str;
			re(i, length)
				out << other.num[length - i - 1];
		}
		else{//С�������м�
			int point = -other.Point;
			unsigned int length = other.length;
			re(i, length){
				if (length - i == point)
					out << '.';
				out << other.num[length - i - 1];
			}
		}
	}
	else{//û��С���㡣�в��㡣
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
