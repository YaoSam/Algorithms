#pragma once
#include "common.h"

TEMP bool operator<	(T const & a, T const &b)	{ return	b > a; }
TEMP bool operator>=	(T const & a, T const &b)	{ return	a > b || !(b > a); }
TEMP bool operator<=	(T const & a, T const &b)	{ return	!(a > b); }
TEMP bool operator!=	(T const & a, T const &b)	{ return	!(a == b); }

TEMP T operator+(T const &a, T const &b){
	T ans(a);
	return ans += b;
}
TEMP T operator-(T const &a, T const &b){
	T ans(a);
	return ans -= b;
}
TEMP T operator*(T const &a, T const &b){
	T ans(a);
	return ans *= b;
}


TEMP void Swap(T & a, T &b)
{
	T temp = a; a = b; b = temp;
}


TEMP inline T Max(T const &a, T const &b)
{
	return a > b ? a : b;
}
TEMP inline T Min(T const &a, T const &b)
{
	return a < b ? a : b;
}


TEMP void printArray(T const *a, unsigned int n)
{
	re(i, n)
		std::cout << a[i] << " ";
	std::cout << std::endl;
}