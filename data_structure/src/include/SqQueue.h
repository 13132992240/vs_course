/*
 *
 * Create By TangNi,  20180408
 *
 */
 

#ifndef SQQUEUE_H
#define SQQUEUE_H 1

#include "basic.h"

template <typename T> struct SqQueue {
	T data[MAX_SIZE];
	int front;
	int rear;
};


template <typename T> void InitQueue(SqQueue<T> *&q)
{
	q = new SqQueue<T>;
	q->front = q->rear = -1;
}


template <typename T> void DestroyQueue(SqQueue<T> *&q)
{
	delete q;
}


template <typename T> bool QueueEmpty(SqQueue<T> *q)
{
	return(q->front == q->rear);
}


template <typename T> bool enQueue(SqQueue<T> *&q, T e)
{
	if (q->front == MAX_SIZE - 1) {  //���������
		return false;
	}
	q->rear++;
	q->data[q->rear] = e;
	return true;
}


template <typename T> bool deQueue(SqQueue<T> *&q, T &e)
{
	if (q->front == q->rear) {  //�ӿ������
		return false;
	}
	q->front++;
	e = q->data[q->front];
	return true;
}


//circular queue
template <typename T> void InitCQueue(SqQueue<T> *&q)
{
	q = new SqQueue<T>;
	q->front = q->rear = 0;
}


template <typename T> void DestroyCQueue(SqQueue<T> *&q)
{
	delete q;
}



//�Ӷ�β����
template <typename T> bool enCQueueR(SqQueue<T> *&q, T e)
{
	if ((q->rear + 1) % MAX_SIZE == q->front) {
		return false;
	}
	q->rear = (q->rear + 1) % MAX_SIZE;
	q->data[q->rear] = e;
	return true;
}


//�Ӷ�ͷ����
template <typename T> bool enCQueueF(SqQueue<T> *&q,T e)
{
	if ((q->rear + 1) % MAX_SIZE == q->front) {
		return false;
	}
	q->data[q->front] = e;
	q->front = (q->front - 1 + MAX_SIZE) % MAX_SIZE;  //�޸�ͷָ��
	return true;
}


//�Ӷ�ͷɾ��
template <typename T> bool deCQueueF(SqQueue<T> *&q, T &e)
{
	if (q->front == q->rear) {
		return false;
	}
	q->front = (q->front + 1) % MAX_SIZE;
	e = q->data[q->front];
	return true;
}


//�Ӷ�βɾ��
template <typename T> bool deCQueueR(SqQueue<T> *&q, T &e)
{
	if (q->rear == q->front) {
		return false;
	}
	e = q->data[q->rear];
	q->rear = (q->rear - 1 + MAX_SIZE) % MAX_SIZE;
	return true;
}



//��3.7 count�����βָ��
template <typename T> struct QuType
{
	T data[MAX_SIZE];
	int front;
	int count;
};

template <typename T> void InitQueue1(QuType<T> *&qu)
{
	qu = new QuType<T>;
	qu->front = 0;
	qu->count = 0;
}


template <typename T> bool EnQueue1(QuType<T>  *&qu, T x)
{
	int rear;
	if (qu->count == MAX_SIZE) {
		return false;
	}
	else {
		rear = (qu->front + qu->count) % MAX_SIZE;  //���βλ��
		rear = (rear + 1) % MAX_SIZE;
		qu->data[MAX_SIZE] = x;
		qu->count++;
		return true;
	}
}


template <typename T> bool DeQueue1(QuType<T>  *&qu, T &x)
{
	if (qu->count == 0) {
		return false;
	}
	else {
		qu->front = (q->front + 1) % MAX_SIZE;
		x = qu->data[qu->front];
		qu->count--;
		return true;
	}
}


template <typename T> bool QueueEmpty1(QuType<T>  *qu)
{
	return (qu->count == 0);
}


//��ⱨ������ P108
void number(int n)
{
	int i;
	int e=0;
	SqQueue<int> *q;        //���ζ���ָ��q
	InitCQueue(q);
	for (i = 1; i <=n; i++) {
		enCQueueR(q, i);
	}
	cout << "��������˳��" << endl;
	while (!QueueEmpty(q)) {
		deCQueueF(q, e);
		cout << '\t' << e;
		if (!QueueEmpty(q)) {
			deCQueueF(q, e);
			enCQueueR(q, e);
		}
	}
	cout << endl;
	DestroyCQueue(q);
}

void SqQueueExample()
{
	int n = 8;
	cout << "��ʼ����" << endl;
	for (int i = 1; i <= n; i++) {
		cout << '\t' << i;
	}
	cout << endl;
	number(n);
}

#endif
