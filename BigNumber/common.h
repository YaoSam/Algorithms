#pragma once
#undef  re
#define re(i,n) for(unsigned int i=0;i<n;i++)
#undef  TEMP
#define TEMP template<class T>

//Ҫ����>��!=
TEMP inline bool operator<	(T const & a, T const &b);
TEMP inline bool operator>=	(T const & a, T const &b);
TEMP inline bool operator<=	(T const & a, T const &b);
TEMP inline bool operator!=	(T const & a, T const &b);

TEMP T operator+(T const &a, T const &b);
TEMP T operator-(T const &a, T const &b);

TEMP inline void Swap(T & a, T &b);

TEMP inline T Max(T const &a, T const &b);

TEMP void printArray(T const *a, unsigned int n);