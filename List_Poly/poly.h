#define re(i,n) for(int i=0;i<n;i++)
#include <iostream>
#include "../Data Sturcture/list.h"
#include "../Data Sturcture/list.cpp"

using namespace std;
struct node
{
	int n;
	double coef;
	node(int const &N=0, double const &Coef=0) :n(N), coef(Coef){}
};
ostream& operator<<(ostream& out, const node & other);
istream& operator>>(istream& in, node& other);

class poly
{
	ME::list<node> List;
public:
	poly(node a[]=nullptr, int n=0);
	friend poly operator+(const poly& a, const poly& b);
	friend ostream& operator<<(ostream& out, const poly& other);
};
poly operator+(const poly& a, const poly& b);
ostream& operator<<(ostream& out, const poly& other);
