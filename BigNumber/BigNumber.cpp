#pragma once
#include "BigNumber.h"
#include <math.h>
#include <sstream>
unsigned int R::getDigit(int num)const{
	unsigned int count = 0;
	while (num > 0){
		count++;
		num /= 10;
	}
	return count;
}
int *R::EmptyIntSpace(unsigned int size)const{
	int *ans = new int[size];
	memset(ans, 0, sizeof(int)*size);
	return ans;
}

void R::Create(std::string num){
	sign=(num[0] == '-');
	std::string temp = num;
	unsigned int strLen, left = 0, right = num.length();
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
	unsigned int a = movement / 4, b = movement % 4;//��Ϊ������������
	unsigned int NewSize = getSize(length + movement);
	int *TempData = EmptyIntSpace(NewSize);
	if (b > 0){
		re(i, datasize){//ģ�³˷��Ľ�λ����ÿ�������Ϊ��������
			TempData[a + i] += data[i] * ten[b+1] % 10000;//���沿��
			TempData[a + i + 1] += data[i] * ten[b + 1] / 10000;//ǰ�沿��
		}
	}
	else{
		memcpy(TempData+a, data, sizeof(int)*datasize);
	}
	point -= movement;//��������point���١�
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
		throw "����С����ʧ��\n";
}
void R::clear(){
	sign = false;
	datasize = length = point = 0;
	delete[]data;
	data = NULL;
}

R::R(std::string num){
	Create(num);
}

R::R(double const &d){
	char str[50];//������Ӧ�ò���̫��ɣ�
	sprintf_s(str, "%f", d);
	Create(str);
}
R::R(int const & one){
	std::stringstream ss;
	std::string str;
	ss << one;
	str=ss.str();
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
R& R::operator=(const R & other){
	if (this == &other)return *this;
	delete[] data;
	sign = other.sign;
	length = other.length;
	point = other.point;
	datasize = other.datasize;
	data = EmptyIntSpace(datasize);
	memcpy(data, other.data, sizeof(int)*datasize);
	return *this;
}

R& R::plus(R &other){
	if (sign != other.sign)
		throw "plus()�����÷�\n";
	//����λ����
	AlignPoint(other);
	unsigned int size = Max(other.datasize, datasize);
	int *TempData = EmptyIntSpace(size + 1);
	//�����ļӷ���
	memcpy(TempData, data, sizeof(int)*datasize);
	re(i,other.datasize){
		TempData[i] += other.data[i];
	}
	re(j, size)//��λ
		if (TempData[j] >= 10000){
			TempData[j + 1]++;
			TempData[j] %= 10000;
		}
	//ά������
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

R& R::substract(R& other){
	if (sign != other.sign)
		throw "subtract()�������÷�\n";
	AlignPoint(other);
	//���
	unsigned int size = Max(other.datasize, datasize);
	int *TempData = EmptyIntSpace(size);//�����϶���������λ��
	memcpy(TempData, data, sizeof(int)*datasize);
	//��������
	re(i, other.datasize){
		TempData[i] -= other.data[i];
	}
	//��������
	re(i, size){
		if (TempData[size - i - 1] > 0)	break;
		if (TempData[size - i - 1] < 0){//��һ��Ϊ��
			sign = !sign;
			re(j,size-i)//ȫ��ȡ��
				TempData[j]*=-1;
			size = size - i+1;//���������С
			break;
		}
	}
	//��λ
	re(j, size-1){//��λ�϶�Ϊ����ȫ����������[-9999,9999]
		if (TempData[j] < 0){//��λ
			TempData[j] += 10000;
			TempData[j + 1]--;
		}
	}
	//ά������
	re(i, size){
		if (TempData[size-i-1] > 0){
			length = (size - i - 1) * 4 + getDigit(TempData[size - i - 1]);
			size = size-i;
			break;
		}
	}
	delete[] data;
	data = TempData;
	datasize = size;
	return *this;
}

R& R::operator+=(const R& other){
	R temp(other);//��ΪҪ���������Լ�λ�ơ�����Ҫ�ĳɾֲ�����
	if (other.sign == sign){
		return this->plus(temp);
	}
	else{
		temp.sign = sign;
		return this->substract(temp);
	}
}

R& R::operator-=(const R& other){
	R temp(other);
	if (other.sign == sign){
		return this->substract(temp);
	}
	else{
		temp.sign = sign;
		return this->plus(temp);
	}
}

R& R::operator*=(const R&other){
	int NewSize = other.datasize + datasize;
	int otherSize = other.datasize;
	int* TempData = EmptyIntSpace(NewSize);
	//�����˷�
	re(i, otherSize){
		if (other.data[i] > 0){//��һ��С�жϰɡ���
			re(j, datasize){
				if (data[j] > 0){
					TempData[i + j] += data[j] * other.data[i];
					if (TempData[i + j] >= 10000){
						TempData[i + j + 1] += TempData[i + j] / 10000;
						TempData[i + j] %= 10000;
					}
				}
			}
		}
	}
	//ά��size
	re(i, NewSize){
		if (TempData[NewSize - i - 1] > 0){
			datasize = NewSize - i;
			break;
		}
		if (i == NewSize - 1)
			datasize = 0;
	}
	//ά��length
	length = (datasize - 1) * 4 + getDigit(TempData[datasize - 1]);
	//ά��sign
	sign ^= other.sign;
	//ά��point
	point += other.point;
	delete[] data;
	data = TempData;
	return *this;
}

std::ostream& operator<<(std::ostream &out, R const &other){
	unsigned int DataLen = other.datasize, digit, pointLocation;
	int temp;
	if (other.sign)
		out << '-';
	//�ж����
	if (other.point < 0){
		//////////////////////////////////////////////////////////////////////////
		if (unsigned int(abs(other.point)) >= other.length){//С����������ǰ��
			out << "0." << std::string().assign(abs(other.point) - other.length, '0');
			re(i, DataLen){//ǰ�油�㼴���������
				temp = other.data[DataLen - i - 1];
				digit = other.getDigit(temp);
				if (i != 0 && digit < 4)
					out << zero[4 - digit];
				if (temp != 0)out << temp;
			}
		}
		//////////////////////////////////////////////////////////////////////////
		else{//С�����������м�
			pointLocation = other.length - abs(other.point);//��¼��С���㻹�ж�Զ
			re(i, DataLen){
				temp = other.data[DataLen - i - 1];
				digit = other.getDigit(temp);
				if ((i == 0 && pointLocation <= digit) || pointLocation <= 4) {
					re(j, 4){//��λ���
						if (!(temp < ten[4 - j] && i == 0)){//�ų���λ���������
							out << (temp / ten[(4 - j)]) % 10;
							pointLocation -= 1;
						}
						if (pointLocation == 0){
							out << ".";
							pointLocation--;//Ȼ����Ҳ�������С����
						}
					}
				}
				else{//�������
					if (i != 0 && digit < 4){
						out << zero[4 - digit];
						pointLocation -= 4;
					}
					else if (i == 0)pointLocation -= digit;
					else pointLocation -= 4;
					if (temp != 0)out << temp;
				}
			}
		}
	}
	//////////////////////////////////////////////////////////////////////////
	else{//С���������ֺ��档Ҳ����>10�������
			re(i, DataLen){//���油�㼴���������
				temp = other.data[DataLen - i - 1];
				int digit = other.getDigit(temp);
				if (i != 0 && digit < 4)
					out << zero[4 - digit];
				if (temp != 0)out << temp;
			}
			out << std::string().assign(other.point, '0');
	}
	return out << std::endl;
}
std::istream& operator>>(std::istream &in, R & other){
	std::string str;
	in >> str;
	other.Create(str);
	return in;
}
