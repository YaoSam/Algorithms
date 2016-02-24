#pragma once
#include "BigNumber.h"
#include <math.h>
unsigned int R::CheckLen(unsigned int max){
	length = 0;
	re(i, max)
		if (data[max - i - 1] > 0)
			return length = max - i - 1;
	return length;
}

unsigned int R::getDigit(int num)const{
	unsigned int count = 0;
	while (num > 0)
	{
		count++;
		num /= 10;
	}
	return count;
}
R::R(std::string num):sign(num[0]=='-'){
	std::string temp = num;
	int strLen,left=0,right=num.length();
	//��������
	if (sign)
		temp = temp.substr(1, temp.length());
	//����С����
	strLen = temp.length();
	point = temp.find('.');
	if (point >= 0){
		temp = temp.substr(0, point) + temp.substr(point + 1, temp.length());
			strLen--;
	}
	else point = temp.length();
	//�������ֶ�
	re(i, strLen)
		if (temp[strLen - i - 1] != '0'){
			right = strLen - i - 1;//��¼��һ����Ϊ���λ��
			break;
		}
	point -= right + 1;
	re(i, strLen)
		if (temp[i] != '0'){
			left = i;
			break;
		}
	temp = temp.substr(left, right - left + 1);//��ΪrightҲ��Ϊ0������Ҫ��һ��
	//¼������
	length = right - left + 1;
	datasize = length / 4 + (!length % 4 == 0);
	data = new int[datasize];
	memset(data, 0, sizeof(int)*(datasize));
	re(i,length)
		if (temp[length - i -1] != '0'){
			data[i / 4] += ten[(i) % 4 + 1] * (temp[length - i -  1] - '0');
		}
	//printArray(data,datasize);
	//std::cout << point << std::endl;
}
std::ostream& operator<<(std::ostream &out, R const &other)
{
	unsigned int DataLen = other.datasize, temp, digit,pointLocation;
	int status=0;
	if (other.point < 0){
		if (abs(other.point) >= other.length)
			status = 0;
		else status = 1;
	}
	else status = 2;
	if (other.sign)
		out << '-';
	switch (status)
	{
		case 0:{//С����������ǰ��
			out << "0."<< std::string().assign(abs(other.point) - other.length, '0');
			re(i, DataLen)
			{
				temp = other.data[DataLen - i - 1];
				digit = other.getDigit(temp);
				if (i != 0 && digit < 4)
					out << zero[4 - digit];
				out << temp;
			}
			break;
		}
		case 1:{//С�����������м�
			int count = 0;
			pointLocation = other.length - abs(other.point);
			re(i, DataLen){
				temp = other.data[DataLen - i - 1];
				int digit = other.getDigit(temp);
				if ((i==0&&pointLocation<=digit)||pointLocation<=4) {
					re(j, 4){
						if (!(temp < ten[4 - j] && i == 0))
						{
							out << (temp / ten[(4 - j)]) % 10;
							pointLocation -= 1;
						}
						if (pointLocation == 0)
						{
							out << ".";
							pointLocation--;
						}
					}
				}
				else{
					if (i != 0 && digit < 4)
					{
						out << zero[4 - digit];
						pointLocation-= 4;
					}
					else pointLocation-=digit;
					out << temp;
				}
			}
			break;
		}
		case 2:{//С���������ֺ��档Ҳ����>10�������
			re(i, DataLen){
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
	//if (abs(other.point) >= other.length)
	//	out << std::string().assign(abs(other.point) - other.length+1, '0');
	//re(i, DataLen)
	//{
	//	temp = other.data[DataLen - i - 1];
	//	int digit = other.getDigit(temp);
	//	if (i != 0 && digit < 4)
	//		out << zero[4 - digit];
	//	out << temp;
	//}
	//if (other.point>0)
	//	out << std::string().assign(other.point, '0');
	return out << std::endl;
}

