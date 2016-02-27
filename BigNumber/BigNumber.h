#pragma once
#include "common.cpp"
#include <iostream>
#include <string>
const int ten[5] = { 0, 1, 10, 100, 1000 };		//������λ��
const std::string zero[5] = {"", "0", "00", "000", "0000" };
class R
{
	bool sign;					//����,trueΪ��
	unsigned int length;	//���ֵ�λ��
	int point;					//��ʼλ��λ����Ҳ����*10^point
	int *data;					//���ݶΡ�
	unsigned int datasize;//����Ĵ�С
	R(unsigned int L, int P, bool S, int *D,unsigned int DS) :
		length(L), sign(S), point(P), data(D),datasize(DS){}
	//�򵥳��ú���
	int *EmptyIntSpace(unsigned int size)const;
	unsigned int getDigit(int num)const;//�����������ֵ�λ����
	unsigned int getSize(int len)const{ return len / 4 + (len % 4 != 0); }
	void Create(std::string num);
	R& LeftMove(unsigned int dis);
	void AlignPoint(R &other);
	void clear();
	//���������ļӼ����������Ƿ��š�
	R& plus(R& other);
	R& substract(R& other);
public:
	//��������
	R() :sign(0), length(0), point(0), data(NULL),datasize(0){}
	R(std::string num);
	R(double const &d);
	R(int const & n);
	R(const R & other);
	R& operator=(const R &other);
	virtual ~R(){ delete[] data; }
	friend std::ostream& operator<<(std::ostream &out, R const &other);//������̫TM���ˣ�����
	friend std::istream& operator>>(std::istream &in, R & other);
	//��ѧ�����
	R& operator+=(const R & other);
	R& operator-=(const R & other);
	R& operator*=(const R & other);
	bool operator>(const R & other)const;
	bool operator==(const R & other)const;
};

std::ostream& operator<<(std::ostream &out, R const &other);
std::istream& operator>>(std::istream &in, R & other);
