/*
*
* Create By ChenXiaodie,2018
*
*/


#pragma once
#include "basic.h"


template<typename T> struct LinkNode {
	T data;
	LinkNode<T> *next;
};

template<typename T> void CreateListF(LinkNode<T>  *&L, T a[], int n)
{
	LinkNode<T> *s;
	L = new LinkNode<T>;
	L->next = 0;
	for (int i = 0; i<n; i++) {
		s = new LinkNode<T>;
		s->data = a[i];
		s->next = L->next;
		L->next = s;
	}
}

template<typename T> void CreateListR(LinkNode<T>  *&L, T a[], int n)
{
	LinkNode<T>  *s, *r;
	L = new LinkNode<T>;
	r = L;
	for (int i = 0; i<n; i++) {
		s = new LinkNode<T>;
		s->data = a[i];
		r->next = s;
		r = s;
	}
	r->next = 0;
}

template<typename T> void ListInsert(LinkNode<T> *&L, T x, int n)
{
	LinkNode<T> *p = L, *S;
	for (int i = 0; i < n - 1; i++)
	{
		p = p->next;
	}
	S = new LinkNode<T>;
	S->data = x;
	S->next = p->next;
	p->next = S;
}

template<typename T> void ListDelete(LinkNode<T> *&L, int n)
{
	LinkNode<T> *p = L, *pre = L;
	for (int i = 0; i < n; i++)
	{
		pre = p;
		p = p->next;
	}
	pre->next = p->next;
	delete p;
}

template<typename T> void DispList(LinkNode<T> *L)
{
	LinkNode<T> *p = L->next;
	while (p != 0) {
		cout << "\t" << p->data;
		p = p->next;
	}
	cout << endl;
}

template<typename T> void DestroyList(LinkNode<T> *L)
{
	LinkNode<T> *pre = L, *p = L->next;
	while (p != 0)
	{
		delete pre;
		pre = p;
		p = pre->next;
	}
	delete pre;
}

template<typename T> void deletemaxnode(LinkNode<T> *&L)
{
	LinkNode<T> *p = L->next, *pre = L, *maxp = p, *maxpre = pre;
	while (p != 0) {
		if (maxp->data < p->data) {
			maxp = p;
			maxpre = pre;
		}
		pre = p;
		p = p->next;
	}
	maxpre->next = maxp->next;
	delete maxp;
}


/*
 * Cycle List
 */

template<typename T> void CreateCircularListF(LinkNode<T> *&L, T a[], int n)
{
	LinkNode<T> *s, *r;
	L = new LinkNode<T>;
	L->next = 0;
	for (int i = 0; i<n; i++) {
		s = new LinkNode<T>;
		s->data = a[i];
		if (L->next == 0)
		{
			r = s;
		}
		s->next = L->next;
		L->next = s;
	}

}

template<typename T> void CreateCircularListR(LinkNode<T> *&L, T a[], int n)
{
	LinkNode<T> *s, *r;
	L = new LinkNode<T>;
	r = L;
	for (int i = 0; i<n; i++) {
		s = new LinkNode<T>;
		s->data = a[i];
		r->next = s;
		r = s;
	}
	r->next = L;
}


/*
 *  examples
 */

//���ش�ͷ������ת������
template<typename T> LinkNode<T>* ListReverse(LinkNode<T> *L)
{
	LinkNode<T> *New_head, *Old_head,*temp;
	New_head = 0;          //��һ��Ԫ��Ϊ���ú�����һ��Ԫ�أ���next��ֵΪNULL
	Old_head = L->next;
	while (Old_head) {
		temp = Old_head->next;
		Old_head->next = New_head;   //��תָ�룬�ɺ�һ��Ԫ��ָ��ǰһ��Ԫ��
		New_head = Old_head;        //����Ƶ�һ��Ԫ��
		Old_head = temp;           //����Ƶ�һ��Ԫ��
	}
	L->next = New_head;          //��ͷָ��ָ������Ԫ��
	return L;
}

void LinkNodeExample()
{
	int a[] = { 1, 2, 3, 4, 5 };
	const int n = 5;

	LinkNode<int> *linkedlist = 0;
	CreateListF(linkedlist, a, n);
	DispList(linkedlist);
	DestroyList(linkedlist);

	CreateListR(linkedlist, a, n);
	DispList(linkedlist);

	ListInsert(linkedlist, 3, 6);
	DispList(linkedlist);

	ListDelete(linkedlist, 6);
	DispList(linkedlist);

	//P53 ����2.7��
	deletemaxnode(linkedlist);
	DispList(linkedlist);

	CreateListR(linkedlist, a, n);
	DispList(ListReverse(linkedlist));

}

