#pragma once
#include "poly.h"
#include <algorithm>
istream& operator>>(istream& in, node& other)
{
	return in >> other.coef >> other.n;
}
ostream& operator<<(ostream& out, const node& other)
{
	return out << other.coef << "x^" << other.n;
}


poly::poly(node a[], int n) 
	:List(a,n)
{}


poly operator+(const poly& a, const poly& b)
{
	auto itera = a.List.begin(), iterb = b.List.begin();
	poly ans;
	while(!itera.isEnd()&&!iterb.isEnd())
	{
		if (itera->n < iterb->n)
		{
			ans.List.push_back(*itera);
			++itera;
		}
		else if (iterb->n > iterb->n)
		{
			ans.List.push_back(*iterb);
			++iterb;
		}
		else
		{
			ans.List.push_back(node(itera->n, itera->coef + iterb->coef));
			++iterb;
			++itera;
		}
	}
	while(!itera.isEnd())
	{
		ans.List.push_back(*itera);
		++itera;
	}
	while(!iterb.isEnd())
	{
		ans.List.push_back(*iterb);
		++iterb;
	}
	return ans;
}

ostream& operator<<(ostream& out, const poly& other)
{
	auto iter = other.List.begin();
	while (!iter.isEnd())
	{
		out << *iter << "+";
		++iter;
	}
	return out << endl;
}
