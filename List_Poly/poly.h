#define re(i,n) for(int i=0;i<n;i++)
#include <iostream>
using namespace std;
struct node
{
	int n;
	double coef;
	node* next;
	node(int const &N=0, double const &Coef=0,node* Next=nullptr) :n(N), coef(Coef),next(Next){}
};
ostream& operator<<(ostream& out, const node & other);
istream& operator>>(istream& in, node& other);

class poly
{
	node* head;
	poly(node* h) :head(h){}
public:
	poly(node a[], int n);
	poly(const poly& other);
	~poly();
	friend poly operator+(const poly& a, const poly& b);
	friend ostream& operator<<(ostream& out, const poly& other);
};
poly operator+(const poly& a, const poly& b);
ostream& operator<<(ostream& out, const poly& other);
