#pragma once
#include "BigNumber.h"
#include <math.h>
unsigned int R::getDigit(int num)const{
	unsigned int count = 0;
	while (num > 0)
	{
		count++;
		num /= 10;
	}
	return count;
}
int *R::EmptyIntSpace(unsigned int size)const
{
	int *ans = new int[size];
	memset(ans, 0, sizeof(int)*size);
	return ans;
}

void R::Create(std::string num){
	sign=(num[0] == '-');
	std::string temp = num;
	int strLen, left = 0, right = num.length();
	//调整符号
	if (sign)
		temp = temp.substr(1, temp.length());
	//调整小数点
	strLen = temp.length();
	point = temp.find('.');
	if (point >= 0){
		temp = temp.substr(0, point) + temp.substr(point + 1, temp.length());
		strLen--;
	}
	else point = temp.length();
	//查找数字段
	re(i, strLen)
		if (temp[strLen - i - 1] != '0'){
			right = strLen - i - 1;//记录第一个不为零的位数
			break;
		}
	point -= right + 1;
	re(i, strLen)
		if (temp[i] != '0'){
			left = i;
			break;
		}
	temp = temp.substr(left, right - left + 1);//因为right也不为0。所以要加一。
	//录入数据
	length = right - left + 1;
	datasize = getSize(length);
	data = new int[datasize];
	memset(data, 0, sizeof(int)*(datasize));
	re(i, length)
		if (temp[length - i - 1] != '0'){
			data[i / 4] += ten[(i) % 4 + 1] * (temp[length - i - 1] - '0');
		}
	//printArray(data,datasize);
	//std::cout << point << std::endl;
}
R& R::LeftMove(unsigned int movement){
	if (movement == 0)return *this;
	unsigned int a = movement / 4, b = movement % 4;//分为两个部分来做
	unsigned int NewSize = getSize(length + movement);
	int *TempData = EmptyIntSpace(NewSize);
	if (b > 0){
		re(i, datasize){//模仿乘法的进位，将每个数拆分为两个部分
			TempData[a + i] += data[i] * ten[b+1] % 10000;//后面部分
			TempData[a + i + 1] += data[i] * ten[b + 1] / 10000;//前面部分
		}
	}
	else{
		memcpy(TempData, data, sizeof(int)*datasize);
	}
	point -= movement;//数字增大。point减少。
	length += movement;
	datasize = NewSize;
	delete[] data;
	data = TempData;
	return *this;
}
void R::AlignPoint(R &other){
	if (point > other.point)
		this->LeftMove(point - other.point);
	else if (other.point > point)
		other.LeftMove(other.point - point);
	if (other.point != point)
		throw "调整小数点失败\n";
}
R::R(std::string num):sign(num[0]=='-'){
	Create(num);
}

R::R(double const &d){
	char str[50];//浮点数应该不会太大吧？
	sprintf_s(str, "%f", d);
	Create(str);
}
R::R(int const & one){
	char str[30];
	sprintf_s(str, "%d", one);
	Create(str);
}
R::R(const R & other):
sign(other.sign),
length(other.length),
point(other.point), 
datasize(other.datasize){
	data = new int[datasize];
	memcpy(data, other.data, sizeof(int)*datasize);
}

R& R::plus(const R &other){
	if (sign != other.sign)
		throw "plus()错误用法\n";
	R temp = other;
	//调整位数。
	AlignPoint(temp);
	int size = Max(temp.datasize, datasize);
	int *TempData = EmptyIntSpace(size + 1);
	std::cout << *this << temp;
	//整数的加法。
	memcpy(TempData, data, sizeof(int)*datasize);
	re(i,temp.datasize){
		TempData[i] += temp.data[i];
	}
	re(j, size){//进位
		TempData[j + 1] += TempData[j] / 10000;
		TempData[j] %= 10000;
	}
	//维护变量
	if (TempData[size] > 0){
		length = size * 4 + getDigit(TempData[size]);
		size += 1;
	}
	else{
		length = (size - 1) * 4 + getDigit(TempData[size-1]);
	}
	delete[] data;
	data = TempData;
	datasize = size;
	return *this;
}

R& R::substract(const R& other){
	if (sign != other.sign)
		throw "subtract()，错误用法\n";
	R temp = other;
	int size = Max(temp.datasize, datasize);
	int *TempData = EmptyIntSpace(size);//减法肯定不会增加位数
	AlignPoint(temp);
	//相减
	memcpy(TempData, data, sizeof(int)*datasize);
	re(i, other.datasize){
		TempData[i] -= other.data[i];
	}
	//调整符号
	re(i, size){
		if (TempData[size - i - 1] > 0)	break;
		if (TempData[size - i - 1] < 0){//第一个为负
			sign = !sign;
			re(j,i)//全部取负
				TempData[j]*=-1;
			size = size - i;//更新数组大小
			break;
		}
	}
	re(j, size-1){//首位肯定为正。全部数都属于[-9999,9999]
		if (TempData[j] < 0){//退位
			TempData[j] += 10000;
			TempData[j + 1]--;
		}
	}
	//维护变量
	if (TempData[size] > 0){
		length = size * 4 + getDigit(TempData[size]);
		size += 1;
	}
	else{
		length = (size - 1) * 4 + getDigit(TempData[size - 1]);
	}
	delete[] data;
	data = TempData;
	datasize = size;
	return *this;

}

R& R::operator+=(const R& other){
	return this->plus(other);
}

R& R::operator-=(const R& other){
	return this->substract(other);
}

R& R::operator=(const R & other){
	if (this == &other)return *this;
	//delete[] data;
	sign = other.sign;
	length = other.length;
	point = other.point;
	datasize = other.datasize;
	data = EmptyIntSpace(datasize);
	memcpy(data, other.data, sizeof(int)*datasize);
	return *this;
}

std::ostream& operator<<(std::ostream &out, R const &other)
{
	unsigned int DataLen = other.datasize, temp, digit,pointLocation;
	//判断情况
	int status=0;
	if (other.point < 0){
		if (abs(other.point) >= other.length)
			status = 0;
		else status = 1;
	}
	else status = 2;
	//看情况输出
	if (other.sign)
		out << '-';
	switch (status)
	{
		case 0:{//小数点在数字前面
			out << "0."<< std::string().assign(abs(other.point) - other.length, '0');
			re(i, DataLen){//前面补零即可正常输出
				temp = other.data[DataLen - i - 1];
				digit = other.getDigit(temp);
				if (i != 0 && digit < 4)
					out << zero[4 - digit];
				out << temp;
			}
			break;
		}
		case 1:{//小数点在数字中间
			pointLocation = other.length - abs(other.point);//记录离小数点还有多远
			re(i, DataLen){
				temp = other.data[DataLen - i - 1];
				int digit = other.getDigit(temp);
				if ((i==0&&pointLocation<=digit)||pointLocation<=4) {
					re(j, 4){//逐位输出
						if (!(temp < ten[4 - j] && i == 0)){//排除首位的特殊情况
							out << (temp / ten[(4 - j)]) % 10;
							pointLocation -= 1;
						}
						if (pointLocation == 0){
							out << ".";
							pointLocation--;//然后再也不会输出小数点
						}
					}
				}
				else{//正常输出
					if (i != 0 && digit < 4){
						out << zero[4 - digit];
						pointLocation-= 4;
					}
					else if(i==0)pointLocation-=digit;
					else pointLocation -= 4;
					if (temp != 0)out << temp;
				}
			}
			break;
		}
		case 2:{//小数点在数字后面。也就是>10的情况。
			re(i, DataLen){//后面补零即可正常输出
				temp = other.data[DataLen - i - 1];
				int digit = other.getDigit(temp);
				if (i != 0 && digit < 4)
					out << zero[4 - digit];
				out << temp;
			}
			out << std::string().assign(other.point, '0');
			break;
		}
	}
	return out << std::endl;
}
