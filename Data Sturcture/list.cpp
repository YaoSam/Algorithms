#pragma  once
#include "list.h"
namespace ME
{
	TEMP
		list<T>::list(T const a[] /* = NULL */, unsigned int n /* = 0 */) :
		head(new node<T>),
		length(n),
		last(head)
	{
		re(i, n)
			last = (last->next = new node<T>(a[i]));
	}

	TEMP
		list<T>::list(list<T> const & other) :
		head(new node<T>),
		length(other.length),
		last(head)
	{
		node<T>* othertemp = other.head->next;
		while (othertemp != NULL)
		{
			last->next = new node<T>(othertemp->data);
			last = last->next;
			othertemp = othertemp->next;
		}
		return;
	}

	TEMP
		list<T>::~list()
	{
		node<T>* temp = head;
		while (head->next != NULL)
		{
			head = temp->next;
			delete temp;
			temp = head;
		}
		delete temp;
	}

	TEMP
		list<T>& list<T>::operator=(list<T> const & other)
	{
		if (this == &other)return *this;
		node<T>* temp = head;
		node<T>* othertemp = other.head->next;
		while (head->next != NULL)
		{
			head = temp->next;
			delete temp;
			temp = head;
		}
		delete temp;
		last = temp = head = new node < T > ;
		while (othertemp != NULL)
		{
			temp->next = new node<T>(othertemp->data);
			temp = temp->next;
			othertemp = othertemp->next;
		}
		length = other.length;
		check_last();
		return *this;
	}

	TEMP
		void list<T>::push_front(T const &x)
	{
		node<T>* temp = head->next;
		head->next = new node<T>(x, temp);
		length++;
		if (last->next != nullptr)
			last = last->next;
		return;
	}

	TEMP
		void list<T>::check_last()
	{
		while (last->next != NULL)
			last = last->next;
	}

	TEMP
		typename list<T>::iterator list<T>::find(T const &x)
	{
		node<T>* temp = head->next;
		while (temp != NULL)
		{
			if (temp->data == x)
				break;
		}
		return iterator(head,temp);//找不到的时候就是NULL
	}

	TEMP
		void list<T>::delNode(T const &x)
	{
		node<T>* temp = head, *delP = NULL;
		while (temp->next)
		{
			if (temp->next->data == x)
			{
				if (last == temp->next)last = temp;
				delP = temp->next;
				temp->next = temp->next->next;
				delete delP;
				length--;
				break;//跟下面就一个差别。
			}
			else temp = temp->next;
		}
		return;
	}

	TEMP void Swap(list<T>& a, list<T>&b)
	{
		Swap(a.head, b.head);
		Swap(a.length, b.length);
		return;
	}

	TEMP
		void list<T>::erase(T const & x)
	{
		node<T>* temp = head, *delP = NULL;
		while (temp->next)
		{
			if (temp->next->data == x)
			{
				delP = temp->next;
				temp->next = temp->next->next;
				delete delP;
				length--;
			}
			else temp = temp->next;
		}
		return;
	}

	//////////////////////////////////////////////////////

	TEMP
	blist<T>::blist(const T* a, unsigned int n):
	head(new bnode<T>),
	lenght(n),
	last(head)
	{
		re(i, n)
		{
			last->post = new bnode<T>(a[i], last);
			last = last->post;
		}
	}

	TEMP
		blist<T>::blist(const blist<T>& other):
		head(new bnode<T>), 
		lenght(other.lenght),
		last(head)
	{
		bnode<T>* temp = other.head->post;
		re(i, lenght)
		{
			last->post = new bnode<T>(temp->data, last);
			last = last->post;
			temp = temp->post;
		}
	}

	TEMP
		blist<T>::~blist()
	{
		head = head->post;
		while (head)
		{
			delete head->pre;
			head = head->post;
		}
	}

	TEMP
	void blist<T>::push_front(const T& x)
	{
		bnode<T>* temp = new bnode<T>(x, head, head->post);
		if (head->post)head->post->pre = temp;
		head->post = temp;
		if (lenght == 0)last = last->post;
		lenght++;
	}

	TEMP
		blist<T>& blist<T>::operator=(const blist<T>& other)
	{
		if (this == &other)	return *this;
		head = head->post;
		while (head)
		{
			delete head->pre;
			head = head->post;
		}
		head = last = new bnode < T > ;
		bnode<T>* temp = other.head->post;
		lenght = other.lenght;
		re(i, lenght)
		{
			last->post = new bnode<T>(temp->data, last);
			last = last->post;
			temp = temp->post;
		}
		return *this;
	}

	TEMP
		void blist<T>::DelNode(const T& x)
	{
		bnode<T>* temp = head->post;
		while (temp)
		{
			if (temp->data == x)
			{
				lenght--;
				temp->pre->post = temp->post;//肯定存在temp->pre
				if (temp->post)
					temp->post->pre = temp->pre;
				else
					last = temp->pre;
				delete temp;
				return;
			}
			temp = temp->post;
		}
	}

	TEMP
		void blist<T>::erase(const T& x)
	{
		bnode<T>* temp = head->post,*temp2;
		while (temp)
		{
			temp2 = temp->post;
			if (temp->data == x)
			{
				lenght--;
				temp->pre->post = temp->post;//肯定存在temp->pre
				if (temp->post)
					temp->post->pre = temp->pre;
				else
					last = temp->pre;
				delete temp;
			}
			temp = temp2;
		}
	}
}