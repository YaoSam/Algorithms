#pragma once
#include "common.cpp"
#include <iostream>
#include <string>
const int ten[5] = { 0, 1, 10, 100, 1000 };		//������λ��
const std::string zero[5] = {"", "0", "00", "000", "0000" };
class R
{
	bool sign;					//����
	unsigned int length;	//���ֵ�λ��
	int point;					//��ʼλ��λ����Ҳ����*10^point
	int *data;					//���ݶΡ�
	R(unsigned int L, int P, bool S, int *D) :
		length(L), sign(S), point(P), data(D){}
	unsigned int CheckLen(unsigned int max);
	unsigned int getDigit(int num)const;
public:
	R() :sign(1), length(0), point(0), data(NULL){}
	R(std::string num);
	R(double const &d);
	R(const R & other);
	R& operator=(const R &other);
	virtual ~R(){}
	friend std::ostream& operator<<(std::ostream &out, R const &other);
};

std::ostream& operator<<(std::ostream &out, R const &other);
