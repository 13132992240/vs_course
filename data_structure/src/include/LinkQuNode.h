#pragma once

#include "basic.h"
#include"LinkNode.h"

//������
template <typename T> struct DataNode
{
	T data;
	DataNode<T> *next;
};

//����
template <typename T> struct LinkQuNode
{
	DataNode<T> *front;
	DataNode<T> *rear;
};


template <typename T> void InitQueue(LinkQuNode<T> *&q)
{
	q = new LinkQuNode<T>;
	q->front = q->rear = NULL;
}


template <typename T> void DestroyQueue(LinkQuNode<T> *&q)
{
	DataNode<T> *pre = q->front, *p;
	if (pre != NULL) {
		p = pre->next;
		while (p != NULL) {
			delete pre;
			pre = p;
			p = p->next;
		}
		delete pre;//�ͷ����һ�����ݽ��
	}
	delete q;//�ͷ����ӽ��
}


template <typename T> bool QueueEmpty(LinkQuNode<T> *q)
{
	return(q->rear == NULL);
}


template <typename T> void enQueue(LinkQuNode<T> *&q, T e)
{
	DataNode<T> *p;
	p = new DataNode<T>;//�����µĽ��
	p->data = e;
	p->next = NULL;
	if (q->rear == NULL) {
		q->rear = q->front = p;
	}
	else {
		q->rear->next = p;//�����������β������rearָ����
		q->rear = p;
	}
}

template <typename T> bool deQueue(LinkQuNode<T> *&q, T &e)
{
	DataNode<T> *t;
	if (q->rear == NULL) {
		return false;
	}
	t = q->front;
	if (q->front == q->rear) {//ֻ��һ�����ݽ��ʱ
		q->front = q->rear = NULL;
	}
	else {
		q->front = q->front->next;
	}
	e = t->data;
	delete t;
	return true;
}

///////////////////////////////////////text///////////////////////////////////

void LinkQuNodeexample()
{
	int i, e;
	int Q[] = { 1,2,3,4,5 };
	LinkQuNode<int> *q;
	InitQueue(q);
	for (i = 0; i < 5; i++) {
		enQueue(q, Q[i]);
	}
	for (i = 0; i < 5; i++) {
		deQueue(q, e);
		cout << '\t' << e << endl;  //������Ԫ�س���
	}
	DestroyQueue(q);
	cout << endl;
}

////////////////////////example/////ѭ�������������///////////////////////


template <typename T> void InitQueue_S(LinkNode<T> *&rear)
{
	rear = NULL;
}


template <typename T> void enQueue_S(LinkNode<T> *&rear, T e)
{
	LinkNode<T> *p;
	p = new LinkNode<T>;
	p->data = e;
	if (rear == NULL) {
		p->next = p;
		rear = p;
	}
	else {
		p->next = rear->next;
		rear->next = p;
		rear = p;
	}
}


template <typename T> bool deQueue_S(LinkNode<T> *&rear, T &e)
{
	LinkNode<T> *t;
	if (rear == NULL) {
		return false;
	}
	else if (rear->next==rear) {
		e = rear->data;
		delete rear;
		rear = NULL;
	}
	else {
		t = rear->next;
		e = t->data;
		rear->next = t->next;
		delete t;
	}
	return true;
}


template <typename T> bool queueEmpty_S(LinkNode<T> *rear)
{
	return(rear == NULL);
}


void S_LinkQuNodeexample()
{
	int i, e;
	int M[] = { 6,7,8,9 };
	LinkNode<int> *rear;
	InitQueue_S(rear);
	for (i = 0; i < 4; i++) {
		enQueue_S(rear, M[i]);
	}
	for (i = 0; i < 4; i++) {
		deQueue_S(rear, e);
		cout << '\t' << e << endl; //������Ԫ�س���
	}
}