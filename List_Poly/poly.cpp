#include "poly.h"

istream& operator>>(istream& in, node& other)
{
	return in >> other.coef >> other.n;
}
ostream& operator<<(ostream& out, const node& other)
{
	return out << other.coef << "x^" << other.n;
}


poly::poly(node a[], int n) 
{
	head = new node;
	node* temp = head;
	re(i, n)
	{
		temp->next = new node(a[i].n,a[i].coef);
		temp = temp->next;
	}
}

poly::poly(const poly& other)
{
	head = new node;
	node* temp = head;
	node* temp_other = other.head->next;
	while (temp_other)
	{
		temp->next = new node(temp_other->n, temp_other->coef);
		temp = temp->next;
		temp_other = temp_other->next;
	}
}

poly::~poly()
{
	node* temp = head;
	while (head)
	{
		temp = temp->next;
		delete head;
		head = temp;
	}
}

poly operator+(const poly& a, const poly& b)
{
	node* temp=new node;
	node* head = temp;
	node* atemp = a.head->next, *btemp = b.head->next;
	while (atemp&&btemp)
	{
		if (atemp->n < btemp->n)
			temp->next = new node(atemp->n, atemp->coef);
		else if (atemp->n > btemp->n)
			temp->next = new node(btemp->n, btemp->coef);
		else 
			temp->next = new node(atemp->n, atemp->coef + btemp->coef);
		if (temp->next->coef == 0)
		{
			delete temp->next;
			temp->next = nullptr;
		}
		else
		{
			temp = temp->next;
		}
		atemp = atemp->next;
		btemp = btemp->next;
	}
	while (atemp||btemp)
	{
		if (atemp)
		{
			temp->next = new node(atemp->n, atemp->coef);
			atemp = atemp->next;
		}
		else
		{
			temp->next = new node(btemp->n, btemp->coef);
			btemp = btemp->next;
		}
		temp = temp->next;
	}
	return poly(head);
}

ostream& operator<<(ostream& out, const poly& other)
{
	node* temp= other.head->next;
	while (temp)
	{
		out << (*temp) << '+';
		temp = temp->next;
	}
	return out << endl;;
}
