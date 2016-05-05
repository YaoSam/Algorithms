#pragma once
#include "normal2.h"
#include "normal.cpp"
#include <iostream>
#include <iterator>
namespace ME
{
	const int OriginalSize = 10;
	TEMP
	class array
	{
		T *data;
		int size;
		int top;
		void expend();
	public:
		//friend class array<T>::iterator;
		template<class deri_iter>
		class base_iter
		{
		protected:
			T *root, *end;
			T* P;
		public:
			base_iter(T* r, T *p, T* e) :root(r), P(p), end(e){}
			base_iter(array& Array) :root(Array.data), P(Array.data), end(Array.data + Array.top + 1){}
			void goFirst()						{ P = root; }
			bool isEnd()const					{ return P == end; }
			bool CheckRange()					{ return P >= root&&P < end; }
			T& operator*()const { return (*P); }
			T* operator->()const { return P; }
			deri_iter& operator++()		{ ++P; return static_cast<deri_iter&>(*this); }
			deri_iter& operator--()		{ --P; return static_cast<deri_iter&>(*this); }
			deri_iter operator++(int)	{ return deri_iter(root, P++, end); }
			deri_iter operator--(int)	{ return deri_iter(root, P--, end); }
			deri_iter operator+(const int movement)const{ return deri_iter(root, P + movement, end); }
			deri_iter operator-(const int movement)const{ return deri_iter(root, P - movement, end); }
			deri_iter& operator+=(const int movement)	{ P += movement; return static_cast<deri_iter&>(*this); }
			deri_iter& operator-=(const int movement)	{ P -= movement; return static_cast<deri_iter&>(*this); }
			int operator-(const deri_iter& other)const	{ return P - other.P; }
			bool operator==(const deri_iter& other)const{ return P == other.P; }
			bool operator>(const deri_iter& other)const	{ return P > other.P; }
		};
		class iterator:public base_iter<iterator>, public std::iterator<std::random_access_iterator_tag,T>
		{
		public:
			//下面5句与继承base_iter等价。为了trait服务。
			//typedef std::random_access_iterator_tag iterator_category;
			//typedef T value_type;
			//typedef typename std::allocator<T>::difference_type difference_type;
			//typedef typename std::allocator<T>::const_pointer pointer;
			//typedef typename std::allocator<T>::const_reference reference;
			iterator(T* r, T *p, T* e) :base_iter<iterator>(r, p, e){}
			iterator(array& Array) :base_iter<iterator>(Array){}
		};
		class const_iterator :public base_iter<const_iterator>, public std::iterator<std::input_iterator_tag,T>
		{
		public:
			const_iterator(const T* r, const T *p, const T*e) :
				base_iter<const_iterator>
				(	const_cast<T*>(r),
					const_cast<T*>(p),
					const_cast<T*>(e))
			{}
			const_iterator(const array& Array) :base_iter<const_iterator>(const_cast<array&>(Array)){}
			const T& operator*()const  { return (*P); }
			const T* operator->()const { return P; }
		};
		array(unsigned int n) :
			size(n), top(-1)
		{
			data = new T[size];//天知道为什么要写在下面。
		}
		array() :
			size(OriginalSize), top(-1)
		{
			data = new T[size];
		}
		array(T const *D, unsigned int n) :
			top(int(n) - 1), size(n)
		{
			data = new T[size];
			memcpy(data, D, sizeof(T)*n);
		}
		array(const array<T>& other);
		array<T>& operator=(const array<T>& other);
		~array(){ delete[] data; }
		const T& operator[](unsigned int n)const
		{
			if (n >= size)throw "OUT OF SIZE!";
			return data[n];
		}
		T& operator[](unsigned int n)
		{
			if (n >= size)throw "OUT OF SIZE!";
			if (int(n) > top)top = n;
			return data[n];
		}
		void push(const T &one);
		const int& Top()const	{ return top; }
		const int& Size()const	{ return size; }
		iterator begin()		{ return iterator(*this); }
		const_iterator begin()const { return const_iterator(*this); }
		const_iterator cbegin()const{ return const_iterator(*this); }
		iterator end()				{ return iterator(data, data + top + 1, data + top + 1); }
		const_iterator end()const	{ return const_iterator(data, data + top + 1, data + top + 1); }
		const_iterator cend()const	{ return const_iterator(data, data + top + 1, data + top + 1); }
		friend std::ostream& operator<<(std::ostream& out, const array<T>& other)
		{
			re(i, other.top + 1)
				out << other.data[i] << " ";
			return out << std::endl;
		}
	};

	TEMP
		using arr_iterator = typename array<T>::iterator;

}